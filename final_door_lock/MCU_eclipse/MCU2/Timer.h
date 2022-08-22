/*
 * Timer.h
 *
 *  Created on: Jul 13, 2022
 *      Author: Habiba
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	TIMER0, TIMER1, TIMER2
}TIMERS_ID;

typedef enum
{
	TIMER_OVF, TIMER_CTC
}TIMERS_Mode;

typedef enum
{
	NO_CLOCK_TIMER01, F_CPU_1_TIMER01, F_CPU_8_TIMER01, F_CPU_64_TIMER01, F_CPU_256_TIMER01,
	F_CPU_1024_TIMER01
}TIMERS01_Prescaler;

/*As timer 2 prescaler is different from timer 0 and timer 1*/
typedef enum
{
	NO_CLOCK_TIMER2, F_CPU_1_TIMER2, F_CPU_8_TIMER2, F_CPU_32_TIMER2, F_CPU_64_TIMER2,
	F_CPU_128_TIMER2, F_CPU_256_TIMER2, F_CPU_1024_TIMER2
}TIMER2_Prescaler;

typedef struct
{
	TIMERS_ID timer_id;
	TIMERS_Mode timer_mode;
	TIMERS01_Prescaler prescaler;
	uint16 initial_value;
	uint16 compare_value;
}TIMERS01_ConfigType;

typedef struct
{
	TIMERS_Mode timer_mode;
	TIMER2_Prescaler prescaler;
	uint8 initial_value;
	uint8 compare_value;
}TIMER2_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timers01_Init(const TIMERS01_ConfigType * Config_Ptr);
void Timer2_Init(const TIMER2_ConfigType * Config_Ptr);
void Timer0_SetCallBack(void(*a_ptr)(void));
void Timer1_SetCallBack(void(*a_ptr)(void));
void Timer2_SetCallBack(void(*a_ptr)(void));
void Timers_DeInit(TIMERS_ID id);


#endif /* TIMER_H_ */
