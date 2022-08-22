/*
 * Timer.c
 *
 *  Created on: Jul 12, 2022
 *      Author: Habiba
 */
#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timers01_Init(const TIMERS01_ConfigType * Config_Ptr)
{
	if(Config_Ptr->timer_id == TIMER0)
	{
		if(Config_Ptr->timer_mode == TIMER_OVF)
		{
			TCNT0 = Config_Ptr->initial_value; //Set Timer initial value to a user defined value
			TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
			/* Configure the timer control register
			 * 1. Non PWM mode FOC0=1
			 * 2. Normal Mode WGM01=0 & WGM00=0
			 * 3. Normal Mode COM00=0 & COM01=0
			 * 4. clock = User defined
			 */
			TCCR0 = (1<<FOC0);
			TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->prescaler);
		}
		else if(Config_Ptr->timer_mode == TIMER_CTC)
		{
			TCNT0 = Config_Ptr->initial_value; //Set Timer initial value to a user defined value
			OCR0  = Config_Ptr->compare_value; // Set Compare Value
			TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
			/* Configure timer0 control register
			 * 1. Non PWM mode FOC0=1
			 * 2. CTC Mode WGM01=1 & WGM00=0
			 * 3. No need for OC0 in this example so COM00=0 & COM01=0
			 * 4. clock = User defined
			 */
			TCCR0 = (1<<FOC0) | (1<<WGM01);
			TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->prescaler);
		}
	}

	else if(Config_Ptr->timer_id == TIMER1)
	{
		if(Config_Ptr->timer_mode == TIMER_OVF)
		{
			TCNT1 = Config_Ptr->initial_value;		/* Set timer1 initial count to a user defined value */

			TIMSK |= (1<<TOIE1); /* Enable Timer1 Overflow mode Interrupt */

			/* Configure timer control register TCCR1A
			 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
			 * 2. FOC1A=1 FOC1B=0
			 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 0)
			 */
			TCCR1A = (1<<FOC1A);

			/* Configure timer control register TCCR1B
			 * 1. Overflow Mode WGM12=0 WGM13=0 (Mode Number 0)
			 * 2. Prescaler = User defined
			 */
			TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->prescaler);
		}
		else if(Config_Ptr->timer_mode == TIMER_CTC)
		{
			TCNT1 = Config_Ptr->initial_value;		/* Set timer1 initial count to a user defined value */

			OCR1A = Config_Ptr->compare_value;    /* Set the Compare value to a user defined value */

			TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */

			/* Configure timer control register TCCR1A
			 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
			 * 2. FOC1A=1 FOC1B=0
			 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
			 */
			TCCR1A = (1<<FOC1A);

			/* Configure timer control register TCCR1B
			 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
			 * 2. Prescaler = User defined
			 */
			TCCR1B = (1<<WGM12);
			TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->prescaler);
		}
	}
}

void Timer2_Init(const TIMER2_ConfigType * Config_Ptr)
{
	if(Config_Ptr->timer_mode == TIMER_OVF)
	{
		TCNT2 = Config_Ptr->initial_value; //Set Timer initial value to a user defined value
		TIMSK |= (1<<TOIE2); // Enable Timer2 Overflow Interrupt
		/* Configure the timer control register
		 * 1. Non PWM mode FOC2=1
		 * 2. Normal Mode WGM21=0 & WGM20=0
		 * 3. Normal Mode COM21=0 & COM20=0
		 * 4. clock = User defined
		 */
		TCCR2 = (1<<FOC2);
		TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->prescaler);
	}
	else if(Config_Ptr->timer_mode == TIMER_CTC)
	{
		TCNT2 = Config_Ptr->initial_value; //Set Timer initial value to a user defined value
		OCR2  = Config_Ptr->compare_value; // Set Compare Value
		TIMSK |= (1<<OCIE2); // Enable Timer0 Compare Interrupt
		/* Configure timer2 control register
		 * 1. Non PWM mode FOC2=1
		 * 2. CTC Mode WGM21=1 & WGM20=0
		 * 3. No need for OC2 in this example so COM20=0 & COM21=0
		 * 4. clock = User defined
		 */
		TCCR2 = (1<<FOC2) | (1<<WGM21);
		TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->prescaler);
	}
}

void Timer0_SetCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr0 = a_ptr;
}

void Timer1_SetCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr1 = a_ptr;
}

void Timer2_SetCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr2 = a_ptr;
}

void Timers_DeInit(TIMERS_ID id)
{
	if(id == TIMER0)
	{
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0 = 0;
		TIMSK &= ~(1<<TOIE0) &~ (1<<OCIE0);
	}
	else if(id == TIMER1)
	{
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		OCR1A = 0;
		TIMSK &= ~(1<<TOIE1) &~ (1<<OCIE1A);
	}
	else if(id == TIMER2)
	{
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2 = 0;
		TIMSK &= ~(1<<TOIE2) &~ (1<<OCIE2);
	}

}
