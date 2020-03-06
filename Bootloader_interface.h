/*
 * Bootloader_interface.h
 *
 *  Created on: 20 Feb 2020
 *      Author: Yahia
 */

#ifndef BOOTLOADER_INTERFACE_H_
#define BOOTLOADER_INTERFACE_H_

/* Module Version 1.0.0 */
#define BOOTLOADER_INTERFACE_SW_MAJOR_VERSION           (1U)
#define BOOTLOADER_INTERFACE_SW_MINOR_VERSION           (0U)
#define BOOTLOADER_INTERFACE_SW_PATCH_VERSION           (0U)

#define STD_HIGH		0x01
#define STD_LOW			0x00

#define STD_ACTIVE		0x01
#define STD_IDLE		0x00

#define STD_ON			0x01
#define STD_OFF			0x00

/* Maximum size of data in IHex frame
 * Default:	32*/
#define IHexDataMaxLength	32

typedef uint8 Std_ReturnType;
#define E_OK 					(Std_ReturnType)0
#define E_NOT_OK 				(Std_ReturnType)1

typedef enum{
    IHEX_DATA,	// Data
    IHEX_EOF,	// End Of File
    IHEX_ESA,	// Extended Segment Address
    IHEX_SSA,	// Start Segment Address
    IHEX_ELA,	// Extended Linear Address
    IHEX_SLA	// Start Linear Address
}IHex_RecordTypes;

typedef enum{
	/* Data is completely loaded into buffer and buffer is completed */
	BufferCompletedDataCompleted,

	/* Data is not completely loaded into buffer and buffer is completed */
	BufferCompletedDataNotCompleted,

	/* Data is completely loaded into buffer and buffer is not completed */
	BufferNotCompletedDataCompleted,

	/* Buffer is not completed but the data to be written is not sequentially after previous data*/
	BufferNotCompletedDataNotCompleted,

	/* File is completed */
	FileCompleted
}BufferState;

/* Protection_Type is used to set the value of protection */
typedef uint8 Protection_Type;
#define NoProtection		0U
#define SPMProtection		1U
#define FullProtection		2U
#define LPMProtection		3U

/* BootResetAddress_Type is used to set the value of boot-loader reset address */
typedef uint8 BootResetAddress_Type;
#define ResetAddress			0U
#define ResetAddressPlusOffset	1U

/* BootSizeConfiguration_Type is used to set the size of boot-loader section */
typedef uint8 BootSizeConfiguration_Type;
#define WORDS_256		3U
#define WORDS_512		2U
#define WORDS_1024		1U
#define WORDS_2048		0U

/* IHex_Frame is a structure representing Intel Hex file format */
typedef struct{
	/* Sequence of n bytes of data, represented by 2n hex digits */
	uint8 data[IHexDataMaxLength];

	/* Four hex digits, representing the 16-bit beginning memory address offset of the data */
	uint16 address;

	/* Two hex digits, indicating the number of bytes (hex digit pairs) in the data field */
	uint8 byte_count;

	/* Two hex digits, 00 to 05, defining the meaning of the data field */
	IHex_RecordTypes record_type;

	/* Two hex digits, a computed value that can be used to verify the record has no errors */
	uint8 checksum;

	/* Flag to check whether the frame is valid or not (not intel hex standard) */
	boolean valid;
}IHex_Frame;

/* Bootloader_ConfigType is a struct that contains the configuration parameters of boot-loader */
typedef struct{
	/* Protection Modes (Application Section) */
	Protection_Type AppProtection;

	/* Protection Modes (Boot-loader Section) */
	Protection_Type BootloaderProtection;

	/* Type of reset value of the boot-loader */
	BootResetAddress_Type BootResetAddress;

	/* Size of boot-loader section */
	BootSizeConfiguration_Type BootSizeConfiguration;

	/* Boot after reset mode */
	boolean BootAfterResetEn;

	/* Read while reading mode */
	boolean ReadWhileWritingEn;

	/* SPM interrupt mode */
	boolean InterruptModeEn;
}Bootloader_ConfigType;

BootloaderSection		//Write the following function onto the bootloader section in flash
void Bootloader(void);

AppSection				//Write the following function onto the text section in flash
void Bootloader_Runnable(void);

AppSection				//Write the following function onto the text section in flash
Bootloader_ConfigType Bootloader_GetConfiguration(void);

AppSection				//Write the following function onto the text section in flash
void Bootloader_Uninstall(void);

#endif /* BOOTLOADER_INTERFACE_H_ */
