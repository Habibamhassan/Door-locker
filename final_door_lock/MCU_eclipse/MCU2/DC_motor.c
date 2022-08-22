/*
 * DC_motor.c
 *
 *  Created on: Jul 12, 2022
 *      Author: Habiba
 */
#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "DC_motor.h"
#include "gpio.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the DC Motor:
 * 1. Setup the pins directions by use the GPIO driver which are inputs to the motor.
 * 2. Stop the motor at first.
 */

void DcMotor_Init(void){
	/* Configure the direction of pins which are inputs to the motor */
	GPIO_setupPinDirection(DC_MOTOR_IN1_PORT_ID ,DC_MOTOR_IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN2_PORT_ID ,DC_MOTOR_IN2_PIN_ID,PIN_OUTPUT);
	/*stopping motor by putting the value on the port*/
	GPIO_writePort(DC_MOTOR_IN2_PORT_ID,DC_MOTOR_STOP_VALUE);

}
/*
 * Description :
 * Rotation of the DC Motor:
 * 1. The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	switch (state){
	case 0 :
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID ,DC_MOTOR_IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID ,DC_MOTOR_IN2_PIN_ID,LOGIC_LOW);
		break;
	case 1:
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID ,DC_MOTOR_IN1_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID ,DC_MOTOR_IN2_PIN_ID,LOGIC_LOW);
		break;
	case 2:
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID ,DC_MOTOR_IN1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID ,DC_MOTOR_IN2_PIN_ID,LOGIC_HIGH);
		break;

	}




}


