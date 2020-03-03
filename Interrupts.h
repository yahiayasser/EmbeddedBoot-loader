/*
 * Interrupts.h
 *
 *  Created on: 27 Feb 2020
 *      Author: Yahia
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "Platform_Types.h"
#include <avr/interrupt.h>

void Disable_Interrupts(void);
void Enable_Interrupts(void);


#endif /* INTERRUPTS_H_ */
