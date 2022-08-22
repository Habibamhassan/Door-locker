/*
 * timer2_pwm.h
 *
 *  Created on: Jul 21, 2022
 *      Author: Habiba
 */

#ifndef TIMER2_PWM_H_
#define TIMER2_PWM_H_

#include "std_types.h"

#define TIMER2_OC2_PORT_ID    PORTD_ID
#define TIMER2_OC2_PIN_ID     PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * The function responsible for trigger the Timer2 with the PWM Mode.
 */
void PWM_Timer2_Start(uint8 duty_cycle);



#endif /* TIMER2_PWM_H_ */
