/*
 * control.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Habiba
 */
#define F_CPU	8000000
#include "control.h"

/* Timer0 configurations*/
TIMERS01_ConfigType TIMER0_Config = {TIMER0, TIMER_OVF, F_CPU_1024_TIMER01, 0x00, 0x00};

/*******************************************************************************
 *                      Function Definition                                  *
 *******************************************************************************/

void CONTROL_unlockDoor(void)
{
	DcMotor_Rotate(CW,50);
	Timers01_Init(&TIMER0_Config);
	while(door_opened != 1){}
	door_opened = 0;
	while(door_closing != 1){}
	door_closing = 0;
	while(door_closed != 1){}
	door_closed = 0;
	Timers_DeInit(TIMER0);
}

void CONTROL_alarm(void)
{
	BuzzerOn();
	Timers01_Init(&TIMER0_Config);
	while(buzzer_off != 1){}
	buzzer_off = 0;
	Timers_DeInit(TIMER0);
}

