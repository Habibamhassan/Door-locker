/*
 * MCU2.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Habiba
 */
#define F_CPU	8000000
#include "control.h"
#include "avr/io.h" /* To use the SREG Register */
#include "twi.h"
#include "external_eeprom.h"
#include "uart.h"
#include <util/delay.h>

/* global variable contain the ticks count of the timer */
uint16 g_tick = 0;

/* global variables as flags to know the state of the motor and the buzzer*/
uint8 door_opened = 0;
uint8 door_closing = 0;
uint8 door_closed = 0;
uint8 buzzer_off = 0;

/* global variable used to know which case to enter when the call back function is called*/
uint8 call_back = 0;

/* call back function*/
void CONTROL_ECU_newTimerTick(void)
{
	switch(call_back)
	{
	/* case 1 -> open the door for 33 secs*/
	case 1:
		g_tick++;
		if(g_tick == NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS)
		{
			DcMotor_Rotate(STOP,0);
			door_opened = 1;
		}
		else if(g_tick == (NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS + NUMBER_OF_OVERFLOWS_PER_THREE_SECONDS))
		{
			DcMotor_Rotate(ACW,50);
			door_closing = 1;
		}
		else if(g_tick == (2 * NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS + NUMBER_OF_OVERFLOWS_PER_THREE_SECONDS))
		{
			DcMotor_Rotate(STOP,0);
			door_closed = 1;
			g_tick = 0;
			call_back = 0;
		}
		break;

		/* case 2 -> turn on the buzzer for 1 min*/
	case 2:
		g_tick++;
		if(g_tick == NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE)
		{
			BuzzerOff();
			buzzer_off = 1;
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
	uint8 req_pass[PASS_SIZE]; /* an array used to store the saved password from the EEPROM*/
	uint8 pass[PASS_SIZE]; /* an array used to receive the new password from the user*/
	uint8 re_pass[PASS_SIZE]; /* an array used to receive the re-typed password from the user*/
	uint8 my_pass[PASS_SIZE]; /* an array used to receive the input password from the user*/
	uint8 not_correct_pass = 0; /* a flag used to know if the password is correct or not*/

	/* UART and TWI configurations*/


	/*UART, TWI, DC MOTOR and BUZZER initializations and setting the call back function*/
	Timer0_SetCallBack(CONTROL_ECU_newTimerTick);
	UART_init(9600);
	TWI_init();
	DcMotor_Init();
	BuzzerInit();

	/*Enable I-bit*/
	SREG |= (1<<7);
	while(1)
	{
		/* the CONTROL_ECU is waiting for the HMI_ECU to send a specific signal to proceed*/
		while(UART_recieveByte() != HMI_ECU_READY){}
		UART_sendByte(CONTROL_ECU_READY);
		receive = UART_recieveByte();

		/* CHECK_PASS -> to check for the match of the two entered passwords*/
		if(receive == CHECK_PASS)
		{
			for(i=0; i<PASS_SIZE; i++)
			{
				UART_sendByte(CONTROL_ECU_READY);
				pass[i] = UART_recieveByte();
			}
			for(i=0; i<PASS_SIZE; i++)
			{
				UART_sendByte(CONTROL_ECU_READY);
				re_pass[i] = UART_recieveByte();
			}
			for(i=0; i<PASS_SIZE; i++)
			{
				if(pass[i] != re_pass[i])
				{
					not_correct_pass = 1;
				}
			}

			/* if the two entered passwords are not correct, the CONTROL_ECU will send
			 * a signal for the HMI_ECU to let it know that the two entered passwords
			 * are incorrect*/
			if(not_correct_pass == 1)
			{
				UART_sendByte(CONTROL_ECU_READY);
				while(UART_recieveByte() != HMI_ECU_READY){}
				UART_sendByte(NOT_CORRECT_PASS);
				not_correct_pass = 0;
			}

			/* if the two entered passwords are correct, then the password will be
			 * saved in the EEPROM*/
			else
			{
				UART_sendByte(CONTROL_ECU_READY);
				while(UART_recieveByte() != HMI_ECU_READY){}
				UART_sendByte(0xFF); /* a dummy data*/
				for(i=0; i<PASS_SIZE; i++)
				{
					EEPROM_writeByte((0x0311+i), pass[i]);
					_delay_ms(10);
				}
			}
		}

		/* OPEN_DOOR -> to open the door in case the password is correct*/
		else if(receive == OPEN_DOOR)
		{
			call_back = 1;
			CONTROL_unlockDoor();
		}

		/* ALARM -> to turn the buzzer on in case the password is incorrect*/
		else if(receive == ALARM)
		{
			call_back = 2;
			CONTROL_alarm();
		}

		/* CHECK_SAVED_PASS -> to check the entered password from the user with
		 * the one saved in the EEPROM*/
		else if(receive == CHECK_SAVED_PASS)
		{
			for(i=0; i<PASS_SIZE; i++)
			{
				UART_sendByte(CONTROL_ECU_READY);
				my_pass[i] = UART_recieveByte();
			}
			for(i=0; i<PASS_SIZE; i++)
			{
				EEPROM_readByte((0x0311+i),&(req_pass[i]));
				_delay_ms(10);
			}
			for(i=0; i<PASS_SIZE; i++)
			{
				if(my_pass[i] != req_pass[i])
				{
					not_correct_pass = 1;
				}
			}

			/* if the two entered passwords are not correct, the CONTROL_ECU will send
			 * a signal for the HMI_ECU to let it know that the two entered passwords
			 * are incorrect*/
			if(not_correct_pass == 1)
			{
				UART_sendByte(CONTROL_ECU_READY);
				while(UART_recieveByte() != HMI_ECU_READY){}
				UART_sendByte(NOT_CORRECT_PASS);
				not_correct_pass = 0;
			}
			else
			{
				UART_sendByte(CONTROL_ECU_READY);
				while(UART_recieveByte() != HMI_ECU_READY){}
				UART_sendByte(0xFF); /* a dummy data*/
			}
		}
	}
}


