/*
 * timer2_pwm.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Habiba
 */
#include "timer2_pwm.h"
#include "avr/io.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void PWM_Timer2_Start(uint8 duty_cycle)
{
	TCNT2 = 0; // Set Timer Initial Value to 0

	/* configure the timer
	 * 1. Fast PWM mode FOC2=0
	 * 2. Fast PWM Mode WGM21=1 & WGM20=1
	 * 3. Clear OC2 when match occurs (non inverted mode) COM20=0 & COM21=1
	 * 4. clock = F_CPU/8 CS20=0 CS21=1 CS22=0
	 */
	TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) | (1<<CS21);

	OCR2  = (uint8)(255*((float32)duty_cycle/100));

	/* Configure PB3/ OC0 as output pin --> pin where the PWM signal is generated from Timer0 */
	GPIO_setupPinDirection(TIMER2_OC2_PORT_ID,TIMER2_OC2_PIN_ID,PIN_OUTPUT);
}

