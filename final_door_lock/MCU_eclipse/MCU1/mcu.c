/*
 * mcu.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Habiba
 */

#define F_CPU	8000000
#include "mcu.h"

/* Timer0 configurations*/
TIMERS01_ConfigType TIMER0_Config = {TIMER0, TIMER_OVF, F_CPU_1024_TIMER01, 0x00, 0x00};

/*******************************************************************************
 *                      Function Definition                                  *
 *******************************************************************************/

void HMI_enterPass(uint8* arr)
{
	uint8 i =0;
	do
	{
		arr[i] = KEYPAD_getPressedKey();
		if(arr[i] != ENTER)
		{
			LCD_displayCharacter('*');
		}
		/* Wait 500msec before getting a new press from the keypad buttons, Press time is 500msec */
		_delay_ms(500);
		i++;
	}while(arr[i-1] != ENTER);
}

void HMI_unlockDoor(void)
{
	UART_sendByte(HMI_ECU_READY);
	while(UART_recieveByte() != CONTROL_ECU_READY){}
	UART_sendByte(OPEN_DOOR);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("Open the door");
	LCD_moveCursor(1,0);
	LCD_displayString("Welcome!");
	Timers01_Init(&TIMER0_Config);
	while(door_unlocked != 1){}
	door_unlocked = 0;
	while(door_locking != 1){}
	door_locking = 0;
	while(door_locked != 1){}
	door_locked = 0;
	Timers_DeInit(TIMER0);
}

void HMI_alarm(void)
{
	UART_sendByte(HMI_ECU_READY);
	while(UART_recieveByte() != CONTROL_ECU_READY){}
	UART_sendByte(ALARM);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("Error !!!");
	Timers01_Init(&TIMER0_Config);
	while(error_msg != 1){}
	Timers_DeInit(TIMER0);
	error_msg = 0;
}
