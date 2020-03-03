/*
 * Bootloader_dependencies.h
 *
 *  Created on: 20 Feb 2020
 *      Author: Yahia
 */

#ifndef BOOTLOADER_DEPENDENCIES_H_
#define BOOTLOADER_DEPENDENCIES_H_


/* Module Version 1.0.0 */
#define BOOTLOADER_DEPENDENCIES_SW_MAJOR_VERSION           (1U)
#define BOOTLOADER_DEPENDENCIES_SW_MINOR_VERSION           (0U)
#define BOOTLOADER_DEPENDENCIES_SW_PATCH_VERSION           (0U)

#if(ATMEGA32 != BOOTLOADER_TARGET || ATMEGA16 != BOOTLOADER_TARGET)
#error "The SW version of Bootloader does not suppot this type of micro controller"
#endif

#undef F_CPU

/* uC operating frequency */
#ifndef F_CPU
#define F_CPU 1000000UL //1MHz Clock frequency
#endif


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "UART.h"
#include "WDG.h"

#if(ATMEGA32 == BOOTLOADER_TARGET)

/* Flash size in atmega32 (32Kbytes or 16Kwords) */
#define FLASH_SIZE	32000

/* EEPROM size in atmega32 (1024bytes) */
#define EEPROM_SIZE	1024

/* Flash page size in atmega32 (64 words or 128 bytes) */
#define FLASH_PageSize	64

/* EEPROM page size in atmega32 (4 bytes)  */
#define EEPROM_PageSize	4

#endif

/* Macro expression to jump to the main application (user application) */
#define GoToApp	__asm__ __volatile__("jmp 0x0000")

/* Macro expression to initiate the stack pointer */
#define Atmega32_UpdateSP	               			       \
(__extension__({										   \
	__asm__ __volatile__								   \
	(													   \
		"ldi	r16,0x5F;"								   \
		"out	SPL,r16;"								   \
		"ldi	r16,0x08;"								   \
		"out	SPH,r16;"								   \
	);													   \
}))


//************************************************************************
//						Bootloader_HW_Init
//
//	Function Description    : This API initiate all the HW modules used in
//							  boot-loader code
//	Parameter in			: none
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Sync/Async				: Asynchronous
//	Reentrancy				: Non reentrant
//************************************************************************
void Bootloader_HW_Init(void);

//************************************************************************
//						MC_Reset
//
//	Function Description    : This API reset uC
//	Parameter in			: none
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Sync/Async				: Asynchronous
//	Reentrancy				: Non reentrant
//************************************************************************
void MC_Reset(void);

#endif /* BOOTLOADER_DEPENDENCIES_H_ */
