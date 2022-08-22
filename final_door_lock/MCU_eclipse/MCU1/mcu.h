/*
 * mcu.h
 *
 *  Created on: Jul 21, 2022
 *      Author: Habiba
 */

#ifndef MCU_H_
#define MCU_H_
#include "std_types.h"
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "Timer.h" /* To use Timer0*/
#include <util/delay.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PASS_SIZE	6 /* the password size(5) + 1(the enter key)*/
#define ENTER		13 /* ASCII of enter*/
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

extern uint8 door_unlocked;
extern uint8 door_locking;
extern uint8 door_locked;
extern uint8 error_msg;

/*******************************************************************************
 *                              Function Prototype                           *
 *******************************************************************************/

/* Description:
 * function used to take an input password from the user
 * */
void HMI_enterPass(uint8* arr);

/* Description:
 * function used to write on the screen while the door is unlocking,
 * and send signal to the CONTROL_ECU to open the door
 * */
void HMI_unlockDoor(void);

/* Description:
 * function used to write on the screen while the buzzer is on,
 * and send signal to the CONTROL_ECU to turn on the buzzer
 * */
void HMI_alarm(void);



#endif /* MCU_H_ */
