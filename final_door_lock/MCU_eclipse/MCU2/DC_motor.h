/*
 * DC_motor.h
 *
 *  Created on: Jul 12, 2022
 *      Author: Habiba
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	STOP,CW,ACW
}DcMotor_State;
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* DC MOTOR HW Ports and Pins Ids */
#define DC_MOTOR_IN1_PORT_ID                 PORTB_ID
#define DC_MOTOR_IN1_PIN_ID                  PIN0_ID

#define DC_MOTOR_IN2_PORT_ID                 PORTB_ID
#define DC_MOTOR_IN2_PIN_ID                  PIN1_ID

#define DC_MOTOR_STOP_VALUE                        0xFC
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize the DC Motor:
 * 1. Setup the pins directions by use the GPIO driver which are inputs to the motor.
 * 2. Stop the motor at first.
 */

void DcMotor_Init(void);
/*
 * Description :
 * Rotation of the DC Motor:
 * 1. The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * 2. Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */


