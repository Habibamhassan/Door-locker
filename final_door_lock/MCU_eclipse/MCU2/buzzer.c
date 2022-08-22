/*
 * buzzer.c
 *
 *  Created on: Jul 12, 2022
 *      Author: Habiba
 */
#include "buzzer.h"

void BuzzerInit(void)
{
	 GPIO_setupPinDirection(BUZZER_PORT,BUZZER0,PIN_OUTPUT);
}

void BuzzerOn(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER0,LOGIC_HIGH);
}

void BuzzerOff(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER0,LOGIC_LOW);
}

