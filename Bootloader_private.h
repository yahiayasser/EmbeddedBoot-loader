/*
 * BOOTLOADER_PRIVATE_private.h
 *
 *  Created on: 20 Feb 2020
 *      Author: Yahia
 */

#ifndef BOOTLOADER_PRIVATE_PRIVATE_H_
#define BOOTLOADER_PRIVATE_PRIVATE_H_

/* Module Version 1.0.0 */
#define BOOTLOADER_PRIVATE_SW_MAJOR_VERSION           (1U)
#define BOOTLOADER_PRIVATE_SW_MINOR_VERSION           (0U)
#define BOOTLOADER_PRIVATE_SW_PATCH_VERSION           (0U)

#if(WORDS_256 == BOOTLOADER_BootSizeConfiguration)
#define AppFlashSection_Size			0x3EFF	//Size in words
#define BootloaderFlashSection_Size		0x100	//Size in words
#define App_StartAddress				0x0		//Size in words
#define App_EndAddress					0x3EFF	//Size in words
#define Bootloader_StartAddress			0x3F00	//Size in words
#define Bootloader_EndAddress			0x3FFF	//Size in words
#elif(WORDS_512 == BOOTLOADER_BootSizeConfiguration)
#define AppFlashSection_Size			0x3DFF	//Size in words
#define BootloaderFlashSection_Size		0x200	//Size in words
#define App_StartAddress				0x0		//Size in words
#define App_EndAddress					0x3DFF	//Size in words
#define Bootloader_StartAddress			0x3E00	//Size in words
#define Bootloader_EndAddress			0x3FFF	//Size in words
#elif(WORDS_1024 == BOOTLOADER_BootSizeConfiguration)
#define AppFlashSection_Size			0x3BFF	//Size in words
#define BootloaderFlashSection_Size		0x400	//Size in words
#define App_StartAddress				0x0		//Size in words
#define App_EndAddress					0x3BFF	//Size in words
#define Bootloader_StartAddress			0x3C00	//Size in words
#define Bootloader_EndAddress			0x3FFF	//Size in words
#elif(WORDS_2048 == BOOTLOADER_BootSizeConfiguration)
#define AppFlashSection_Size			0x37FF	//Size in words
#define BootloaderFlashSection_Size		0x800	//Size in words
#define App_StartAddress				0x0		//Size in words
#define App_EndAddress					0x37FF	//Size in words
#define Bootloader_StartAddress			0x3800	//Size in words
#define Bootloader_EndAddress			0x3FFF	//Size in words
#else
#error "Invalid value of BOOTLOADER_BootSizeConfiguration"
#endif

/* NULL Address */
#define NULL_Address	0x00

/* Max Intel Hex frame length (not standard) */
#define MaxFrameLength	45

/* Address's offset in Intel Hex frame */
#define AddressOffset	0x00

/* Page size in bytes*/
#define PageSizeB		(FLASH_PageSize*2)

/* Used to indicate successful frame transmission */
#define BootloaderFrameSuccess		0x5A

/* Used to indicate not successful frame transmission */
#define BootloaderFrameNotSuccess	0x5B

/* Used to indicate the end of transmission */
#define BootloaderFinish			0x5C

/* Used to trigger transmission */
#define IHexFrameStartTransmission	0x5D

AppSection		//Write the following function onto the text section in flash
uint8 ASCII_To_HEX(uint8 ASCII);

AppSection		//Write the following function onto the text section in flash
uint8 string_length(uint8 str[]);

BootloaderSection		//Write the following function onto the bootloader section in flash
IHex_Frame String_To_IHex(uint8* ASCII_Frame);

BootloaderSection		//Write the following function onto the bootloader section in flash
BufferState Bootloader_LoadBuffer(IHex_Frame* IHexFrame, uint8* Buffer, uint8* Count, uint32* NextAdd);

BootloaderSection		//Write the following function onto the bootloader section in flash
void Bootloader_WitrePage (uint32_t PageAddress, uint8_t *Buffer);

#endif /* BOOTLOADER_PRIVATE_PRIVATE_H_ */
