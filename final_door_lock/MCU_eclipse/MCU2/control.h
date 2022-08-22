/*
 * control.h
 *
 *  Created on: Jul 21, 2022
 *      Author: Habiba
 */

#ifndef CONTROL_H_
#define CONTROL_H_
#include "std_types.h"
#include "Timer.h" /* To use Timer0*/
#include "dc_motor.h"
#include "buzzer.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PASS_SIZE	6 /* the password size(5) + 1(the enter key)*/
#define OPEN_DOOR	0x55
#define ALARM		0x44
#define CHECK_SAVED_PASS 0x33
#define SAVE_PASS	0x22
#define CHECK_PASS	0x11
#define NOT_CORRECT_PASS	0x66
#define HMI_ECU_READY 	0x10
#define CONTROL_ECU_READY 	0x20
#define NUMBER_OF_OVERFLOWS_PER_FIFTEEN_SECONDS 457
#define NUMBER_OF_OVERFLOWS_PER_THREE_SECONDS 91
#define NUMBER_OF_OVERFLOWS_PER_ONE_MINUTE 1831

/*******************************************************************************
 *                              Extern Global Variables                        *
 *******************************************************************************/

extern uint8 door_opened;
extern uint8 door_closing;
extern uint8 door_closed;
extern uint8 buzzer_off;

/*******************************************************************************
 *                              Function Prototype                           *
 *******************************************************************************/

/* Description:
 * function used to unlock the door for 33 sec
 * */
void CONTROL_unlockDoor(void);

/* Description:
 * function used to turn on the buzzer for 1 min
 * */
void CONTROL_alarm(void);


#endif /* CONTROL_H_ */
