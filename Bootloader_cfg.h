/*
 * Bootloader_cfg.h
 *
 *  Created on: 20 Feb 2020
 *      Author: Yahia
 */

#ifndef BOOTLOADER_CFG_H_
#define BOOTLOADER_CFG_H_

/* Module Version 1.0.0 */
#define BOOTLOADER_CFG_SW_MAJOR_VERSION           (1U)
#define BOOTLOADER_CFG_SW_MINOR_VERSION           (0U)
#define BOOTLOADER_CFG_SW_PATCH_VERSION           (0U)

/* Operating uC */
#define BOOTLOADER_TARGET ATMEGA32
#define ATMEGA32	1

/* Hex file format */
#define BOOTLOADER_FILE_FORMAT	Intel_HEX
#define Intel_HEX			0
#define Motorola_S_Records	1
#define Raw_Binary			2

/*
	Enable	: STD_ON
	Disable	: STD_OFF
 */
#define BOOTLOADER_CHECKSUM	STD_ON

/*
	Enable	: STD_ON
	Disable	: STD_OFF
 */
#define BOOTLOADER_ReadWhileWriting	STD_OFF

/*
	NoProtection	: No restrictions for SPM or LPM accessing the Application
					  section.
	SPMProtection	: SPM is not allowed to write to the Application section.
	FullProtection	: SPM is not allowed to write to the Application section, and
					  LPM executing from the Boot Loader section is not
					  allowed to read from the Application section. If interrupt
  	  	  	  	  	  vectors are placed in the Boot Loader section, interrupts
  	  	  	  	  	  are disabled while executing from the Application section.
	LPMProtection	: LPM executing from the Boot Loader section is not
  	  	  	  	  	  allowed to read from the Application section. If interrupt
  	  	  	  	  	  vectors are placed in the Boot Loader section, interrupts
  	  	  	  	  	  are disabled while executing from the Application section.
 */
#define BOOTLOADER_AppProtection			NoProtection

/*
	NoProtection	: No restrictions for SPM or LPM accessing the Boot Loader
					  section.
	SPMProtection	: SPM is not allowed to write to the Boot Loader section.
	FullProtection	: SPM is not allowed to write to the Boot Loader section,
					  and LPM executing from the Application section is not
  	  	  	  	  	  allowed to read from the Boot Loader section. If interrupt
  	  	  	  	  	  vectors are placed in the Application section, interrupts
  	  	  	  	  	  are disabled while executing from the Boot Loader section.
	LPMProtection	: LPM executing from the Application section is not allowed
  	  	  	  	  	  to read from the Boot Loader section. If interrupt vectors
  	  	  	  	  	  are placed in the Application section, interrupts are
  	  	  	  	  	  disabled while executing from the Boot Loader section.
 */
#define BOOTLOADER_BootloaderProtection		NoProtection

/*
	Enable	: STD_ON
	Disable	: STD_OFF
 */
#define BOOTLOADER_BootAfterReset	STD_ON

/*
	Enable	: STD_ON
	Disable	: STD_OFF
 */
#define BOOTLOADER_InterruptMode	STD_OFF

/*
	ResetAddress			: Address $0002
	ResetAddressPlusOffset	: Boot Reset Address + $0002
 */
#define BOOTLOADER_BootResetAddress	ResetAddress

/*
	WORDS_256	: 256 word / 512 byte
	WORDS_512	: 512 word / 1024 byte
	WORDS_1024	: 1024 word / 2048 byte
	WORDS_2048	: 2048 word / 4096 byte
 */
#define BOOTLOADER_BootSizeConfiguration	WORDS_2048

#endif /* BOOTLOADER_CFG_H_ */
