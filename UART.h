/*
 * UART.h
 *
 *  Created on: 26 Jan 2019
 *      Author: Yahia
 */

#ifndef UART_H_
#define UART_H_

#include "common_macros.h"
#include "Platform_Types.h"
#include "micro_config.h"


#ifndef Asynchronous
#define Asynchronous 0
#endif

#ifndef Synchronous
#define Synchronous 1
#endif

#ifndef ONE_STOP_BIT
#define ONE_STOP_BIT 0
#endif

#ifndef TWO_STOP_BIT
#define TWO_STOP_BIT 1
#endif

typedef enum{
	BAUD_100, BAUD_200, BAUD_300, BAUD_1200, BAUD_2400, BAUD_4800, BAUD_9600, BAUD_19200, BAUD_38400, BAUD_57600, BAUD_115200
}BAUD_RATE;

typedef enum{
	DISABLE_PARITY, EVEN_PARITY = 2, ODD_PARITY = 3
}PARITY;

typedef enum{
	BIT5, BIT6, BIT7, BIT8, BIT9 = 7
}NUM_BITS;

void UART_Init(volatile const uint8 a_NUM_DATA_BITS, volatile const uint8 a_SYNC, volatile const uint8 a_NUM_STOP_BITS, volatile const uint8 a_BAUD_RATE, volatile const uint8 a_Parity);
void SEND_DATA_UART(volatile const uint8 a_DATA);
uint8 RECEIVE_DATA_UART(void);
void SEND_STRING_UART(const uint8 *STR);
void RECEIVE_STRING_UART(uint8 *Str);


#endif /* UART_H_ */
