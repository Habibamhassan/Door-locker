/*
 * main.c
 *
 *  Created on: Jul 13, 2022
 *      Author: Habiba
 */
#define F_CPU	8000000
#include "mcu.h"
#include "avr/io.h" /* To use the SREG Register */

/* global variable contain the ticks count of the timer */
uint16 g_tick = 0;

/* global variables as flags to know the state of the door and error msg*/
uint8 error_msg = 0;
uint8 door_unlocked = 0;
uint8 door_locking = 0;
uint8 door_locked = 0;

/* global variable used to know which case to enter when the call back function is called*/
uint8 call_back = 0;

/* call back function*/
void HMI_ECU_newTimerTick(void)
{
	switch(call_back)
	{
	/* case 1 -> show the state of the door on the LCD*/
	case 1:
		g_tick++;
		if(g_tick == NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS)
		{
			LCD_sendCommand(LCD_CLEAR_COMMAND);
			LCD_displayString("The door is unlo");
			LCD_moveCursor(1,0);
			LCD_displayString("cked!");
			door_unlocked = 1;
		}
		else if(g_tick == (NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS + NUMBER_OF_OVERFLOWS_PER_THREE_SECONDS))
		{
			LCD_sendCommand(LCD_CLEAR_COMMAND);
			LCD_displayString("The door is lock");
			LCD_moveCursor(1,0);
			LCD_displayString("ing!");
			door_locking = 1;
		}
		else if(g_tick == ((2 * NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS) + NUMBER_OF_OVERFLOWS_PER_THREE_SECONDS))
		{
			LCD_sendCommand(LCD_CLEAR_COMMAND);
			LCD_displayString("The door is lock");
			LCD_moveCursor(1,0);
			LCD_displayString("ed!");
			door_locked = 1;
			g_tick = 0;
			call_back = 0;
		}
		break;

		/* case 2 -> show an error msg on the LCD*/
	case 2:
		g_tick++;
		if(g_tick == NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE)
		{
			LCD_sendCommand(LCD_CLEAR_COMMAND);
			error_msg = 1;
			g_tick = 0;
			call_back = 0;
		}
		break;
	}
}

int main(void)
{
	uint8 i; /* variable used in iterations*/
	uint8 receive; /* variable used to receive a byte from UART*/
	uint8 not_matched = 1; /* a flag used to indicate if the re-typed pass matches the previous one or not*/
	uint8 times = 0; /* a flag used to count the number of times the entered password is wrong*/
	uint8 pass[PASS_SIZE]; /* an array used to take the new password from the user*/
	uint8 re_pass[PASS_SIZE]; /* an array used to take the re-typed password from the user*/
	uint8 my_pass[PASS_SIZE]; /* an array used to take the input password from the user*/
	uint8 options; /* variable used to store the options (+: open door, -: change password)*/

	/* initialization of the UART, LCD and setting the call back function*/

	Timer0_SetCallBack(HMI_ECU_newTimerTick);
	LCD_init();
	UART_init(9600);

	/*Enable I-bit*/
	SREG |= (1<<7);
	while(1)
	{
		while(not_matched == 1) /* the while loop will not be broken until the two passwords match each other*/
		{
			not_matched = 0;
			LCD_sendCommand(LCD_CLEAR_COMMAND);
			LCD_displayString("Enter new pass:");
			LCD_moveCursor(1,0);

			/* take the new password from the user*/
			HMI_enterPass(pass);

			LCD_sendCommand(LCD_CLEAR_COMMAND);
			LCD_displayString("Re-enter pass:");
			LCD_moveCursor(1,0);

			/* take the re-typed password from the user*/
			HMI_enterPass(re_pass);

			/* send the two passwords to the CONTROL_ECU to check if they match each other or not*/
			UART_sendByte(HMI_ECU_READY);
			while(UART_recieveByte() != CONTROL_ECU_READY){}
			UART_sendByte(CHECK_PASS);
			for(i=0; i<PASS_SIZE; i++)
			{
				while(UART_recieveByte() != CONTROL_ECU_READY){}
				UART_sendByte(pass[i]);
			}
			for(i=0; i<PASS_SIZE; i++)
			{
				while(UART_recieveByte() != CONTROL_ECU_READY){}
				UART_sendByte(re_pass[i]);
			}
			while(UART_recieveByte() != CONTROL_ECU_READY){}
			UART_sendByte(HMI_ECU_READY);
			receive = UART_recieveByte();

			/* if the two passwords do not match each other, the user will be asked to try again*/
			if(receive == NOT_CORRECT_PASS)
			{
				LCD_sendCommand(LCD_CLEAR_COMMAND);
				LCD_displayString("Not matched!");
				LCD_moveCursor(1,0);
				LCD_displayString("Try again!");
				_delay_ms(1000);
				not_matched = 1;
			}
		}

		/* if the two passwords match each other, the user will proceed to the second option*/
		if(not_matched == 0)
		{
			LCD_sendCommand(LCD_CLEAR_COMMAND);
			LCD_displayString("+: Open door");
			LCD_moveCursor(1,0);
			LCD_displayString("-: Change pass");
			options = KEYPAD_getPressedKey();
			/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
			_delay_ms(500);

			/* if the user enters + he will be asked to enter the password the unlock the door*/
			if(options == '+')
			{
				not_matched = 1;

				/* the while loop will not be broken until the user enters password wrong for
				 *  3 times and it does not match the one saved in EEPROM*/
				while((times != 3) && (not_matched == 1))
				{
					times++;
					not_matched = 0;
					LCD_sendCommand(LCD_CLEAR_COMMAND);
					LCD_displayString("Enter pass:");
					LCD_moveCursor(1,0);

					HMI_enterPass(my_pass);

					/* the entered password will be sent to the CONTROL_ECU to be checked with
					 * the one saved in the EEPROM*/
					UART_sendByte(HMI_ECU_READY);
					while(UART_recieveByte() != CONTROL_ECU_READY){}
					UART_sendByte(CHECK_SAVED_PASS);
					for(i=0; i<PASS_SIZE; i++)
					{
						while(UART_recieveByte() != CONTROL_ECU_READY){}
						UART_sendByte(my_pass[i]);
					}
					while(UART_recieveByte() != CONTROL_ECU_READY){}
					UART_sendByte(HMI_ECU_READY);
					receive = UART_recieveByte();

					/* if the entered password is wrong, the user will try again and the
					 * number of times will be incremented*/
					if(receive == NOT_CORRECT_PASS)
					{
						LCD_sendCommand(LCD_CLEAR_COMMAND);
						LCD_displayString("Wrong password!");
						_delay_ms(1000);
						not_matched = 1;
					}
				}

				/* if the entered password is correct the door state will appear on the LCD*/
				if(not_matched == 0)
				{
					times = 0;
					call_back = 1;
					HMI_unlockDoor();
				}

				/* if the user entered the password wrong for 3 times an error msg will appear on the LCD*/
				if((times == 3) && (not_matched == 1))
				{
					call_back = 2;
					HMI_alarm();
					times = 0;
					not_matched = 0;
				}
			}

			/* if the user entered - he will be asked to enter the password the change it*/
			else if(options == '-')
			{
				not_matched = 1;

				/* the while loop will not be broken until the user enters password wrong for
				 *  3 times and it does not match the one saved in EEPROM*/
				while((times != 3) && (not_matched == 1))
				{
					times++;
					not_matched = 0;
					LCD_sendCommand(LCD_CLEAR_COMMAND);
					LCD_displayString("Enter pass:");
					LCD_moveCursor(1,0);

					HMI_enterPass(my_pass);

					/* the entered password will be sent to the CONTROL_ECU to be checked with
					 * the one saved in the EEPROM*/
					UART_sendByte(HMI_ECU_READY);
					while(UART_recieveByte() != CONTROL_ECU_READY){}
					UART_sendByte(CHECK_SAVED_PASS);
					for(i=0; i<PASS_SIZE; i++)
					{
						while(UART_recieveByte() != CONTROL_ECU_READY){}
						UART_sendByte(my_pass[i]);
					}
					while(UART_recieveByte() != CONTROL_ECU_READY){}
					UART_sendByte(HMI_ECU_READY);
					receive = UART_recieveByte();

					/* if the entered password is wrong, the user will try again and the
					 * number of times will be incremented*/
					if(receive == NOT_CORRECT_PASS)
					{
						LCD_sendCommand(LCD_CLEAR_COMMAND);
						LCD_displayString("Wrong password!");
						_delay_ms(1000);
						not_matched = 1;
					}
				}

				/* if the entered password is correct, the not_matched flag will be set to be
				 * able to change the password again*/
				if(not_matched == 0)
				{
					times = 0;
					not_matched = 1;
				}

				/* if the user entered the password wrong for 3 times an error msg will appear on the LCD*/
				if((times == 3) && (not_matched == 1))
				{
					call_back = 2;
					HMI_alarm();
					times = 0;
					not_matched = 0;
				}
			}

		}
	}
}
