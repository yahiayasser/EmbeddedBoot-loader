/*
 * UART.c
 *
 *  Created on: 26 Jan 2019
 *      Author: Yahia
 */

#include "UART.h"


void UART_Init(volatile const uint8 a_NUM_DATA_BITS, volatile const uint8 a_SYNC, volatile const uint8 a_NUM_STOP_BITS, volatile const uint8 a_BAUD_RATE, volatile const uint8 a_Parity)
{
	uint16 baud;
	float32 fbaud;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 bits combined with UCSZ21:0 in the UCSRC sets the number
	   of data bits in a frame the receiver and transmitter use.
	   You can also use BIT5, BIT6, BIT7, BIT8, BIT9 for a_NUM_DATA_BITS
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRB = (UCSRB & 0xFB) | (a_NUM_DATA_BITS & 0x04);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation, 1 synchronous Operation.
	   You can also use Synchronous and Asynchronous for a_SYNC.
	 * UPM1:0 for parity bit, You can also use DISABLE_PARITY,
	   EVEN_PARITY, ODD_PARITY for
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1 << URSEL) | (a_SYNC << UMSEL) | (a_NUM_STOP_BITS << USBS);
	UCSRC = (UCSRC & 0xCF) |((a_Parity & 0x03) << 4);
	UCSRC = (UCSRC & 0xF9) |((a_NUM_DATA_BITS & 0x03) << 1);
	if (a_SYNC){
		switch(a_BAUD_RATE){
		case(0):
			fbaud = ((float32)F_CPU / (100 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(1):
			fbaud = ((float32)F_CPU / (200 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(2):
			fbaud = ((float32)F_CPU / (300 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(3):
			fbaud = ((float32)F_CPU / (1200 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(4):
			fbaud = ((float32)F_CPU / (2400 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(5):
			fbaud = ((float32)F_CPU / (4800 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(6):
			fbaud = ((float32)F_CPU / (9600 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(7):
			fbaud = ((float32)F_CPU / (19200 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(8):
			fbaud = ((float32)F_CPU / (38400 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(9):
			fbaud = ((float32)F_CPU / (57600 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(10):
			fbaud = ((float32)F_CPU / (115200 * 2)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		}
	}
	else{
				switch(a_BAUD_RATE){
		case(0):
			fbaud = ((float32)F_CPU / (100 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(1):
			fbaud = ((float32)F_CPU / (200 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(2):
			fbaud = ((float32)F_CPU / (300 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(3):
			fbaud = ((float32)F_CPU / (1200 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(4):
			fbaud = ((float32)F_CPU / (2400 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(5):
			fbaud = ((float32)F_CPU / (4800 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(6):
			fbaud = ((float32)F_CPU / (9600 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(7):
			fbaud = ((float32)F_CPU / (19200 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(8):
			fbaud = ((float32)F_CPU / (38400 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(9):
			fbaud = ((float32)F_CPU / (57600 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		case(10):
			fbaud = ((float32)F_CPU / (115200 * 8)) - 1;
			baud = (int)(fbaud + 0.5);
			break;
		}
	}

	UBRRL = baud;
	UBRRH = baud >> 8;
}


void SEND_DATA_UART(volatile const uint8 a_DATA){
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
	while (BIT_IS_CLEAR(UCSRA, UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR = a_DATA;
}

uint8 RECEIVE_DATA_UART(void){
	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA, RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
	return UDR;
}

void SEND_STRING_UART(const uint8 *STR){
	uint8 count = 0;
	while (STR[count] != '\0'){
		SEND_DATA_UART(STR[count]);
		count++;
	}
}

void SEND_BYTE_UART(volatile const uint8 a_DATA){
	while (BIT_IS_CLEAR(UCSRA, UDRE)){}
	UDR = a_DATA;
}

void RECEIVE_STRING_UART(uint8 *Str){
	uint8 count = 0;
	Str[count] = RECEIVE_DATA_UART();
	while(Str[count] != '\n')
	{
		count++;
		Str[count] = RECEIVE_DATA_UART();
	}
	Str[count] = '\0';
}

