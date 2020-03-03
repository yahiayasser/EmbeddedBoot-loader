/*
 * Abstraction.h
 *
 *  Created on: 26 Feb 2020
 *      Author: Yahia
 */

#ifndef ABSTRACTION_H_
#define ABSTRACTION_H_

/* This file is used to abstract the boot-loader application code from other SW modules */

/* Boot-loader flag address in EEPROM */
#define BootloaderFlagAddress	0x10

/* Macro expression to initiate the communication module used in boot-loader */
#define CommunicationInit	(UART_Init(BIT8, Asynchronous, ONE_STOP_BIT, BAUD_115200, DISABLE_PARITY))

/* Macro expression to get character from the communication module used in boot-loader */
#define GetChar	(RECEIVE_DATA_UART())

/* Macro expression to send character to the communication module used in boot-loader */
#define SendChar(Data) (SEND_DATA_UART(Data))

/* Macro expression to get the value of boot-loader flag in the EEPROM */
#define GetBootloaderFlag	(eeprom_read_byte((const uint8*)0x10))

/* Macro expression to set the value of boot-loader flag in the EEPROM */
#define SetBootloaderFlag	(eeprom_update_byte((const uint8*)0x10, (uint8)TRUE))

/* Macro expression to clear the value of boot-loader flag in the EEPROM */
#define ClearBootloaderFlag	(eeprom_update_byte((const uint8*)0x10, (uint8)FALSE))

/* Macro expression to reset the value of stack pointer */
#define ResetStackPointer	(Atmega32_UpdateSP)

#endif /* ABSTRACTION_H_ */
