/*
 * twi.h
 *
 *  Created on: Jul 12, 2022
 *      Author: Habiba
 */

#ifndef TWI_H_
#define TWI_H_
#include "std_types.h"
#include "twi_config.h"
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);



#endif /* TWI_H_ */
