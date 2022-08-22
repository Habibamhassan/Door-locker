/*
 * buzzer.h
 *
 *  Created on: Jul 12, 2022
 *      Author: Habiba
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"
#include "gpio.h"

#define BUZZER_PORT PORTD_ID
#define BUZZER0 PIN4_ID

void BuzzerInit(void);
void BuzzerOn(void);
void BuzzerOff(void);

#endif /* BUZZER_H_ */
