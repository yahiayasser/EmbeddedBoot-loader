/*
 * Bootloader_private.c
 *
 *  Created on: 2 Mar 2020
 *      Author: Yahia
 */

#include "Bootloader.h"
#include "Bootloader_private.h"
/* Checking between Bootloader and Bootloader_private Modules */
#if ((BOOTLOADER_SW_MAJOR_VERSION != BOOTLOADER_PRIVATE_SW_MAJOR_VERSION)\
		||  (BOOTLOADER_SW_MINOR_VERSION != BOOTLOADER_PRIVATE_SW_MINOR_VERSION)\
		||  (BOOTLOADER_SW_PATCH_VERSION != BOOTLOADER_PRIVATE_SW_PATCH_VERSION))
#error "The SW version of Bootloader_private.h does not match the expected version"
#endif

//************************************************************************
//						Bootloader_LoadBuffer
//
//	Function Description    : Load data of IHex frame to data buffer
//	Parameter in			: IHexFrame: Intel Hex frame
//	Parameter inout         : Count: Used as the cunter and index of data buffer
//							  NextAdd: points to the address of next frame that
//							  should be written
//	Parameter out           : Buffer: Holds the data that should be written onto
//							  the flash
//	Return value            : BufferState: State of the data buffer
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//************************************************************************
BufferState Bootloader_LoadBuffer(IHex_Frame* IHexFrame, uint8* Buffer, uint8* Count, uint32* NextAdd)
{
	/* This API is responsible for storing data into buffer (array) */

	/* Check if this frame is the last frame */
	if(IHexFrame->record_type == IHEX_EOF)
	{
		return FileCompleted;
	}

	/* Check if this frame is the first frame */
	else if(IHexFrame->address == 0x0)
	{
		*NextAdd = IHexFrame->byte_count;
	}

	/* Check if this frame is not sequentially after the previous frame */
	else if(*NextAdd != (IHexFrame->address))
	{
		*NextAdd = (IHexFrame->address);
		return BufferNotCompletedDataNotCompleted;
	}


	else
	{
		*NextAdd = *NextAdd + IHexFrame->byte_count;
	}

	uint8 DataCount = 0;	//Counter

	/* Load data into buffer */
	while((*Count != PageSizeB) && (DataCount != (IHexFrame->byte_count)))
	{
		Buffer[*Count] = IHexFrame->data[DataCount];
		DataCount++;
		*Count = *Count + 1;
	}

	/* Check whether if the buffer is completed and data is complete */
	if((*Count == PageSizeB) && (DataCount == (IHexFrame->byte_count)))
	{
		return BufferCompletedDataCompleted;
	}

	/* Check whether if the buffer is completed and data is not complete */
	else if((*Count == PageSizeB) && (DataCount != (IHexFrame->byte_count)))
	{
		*Count = DataCount;
		return BufferCompletedDataNotCompleted;
	}

	/* Check whether if the buffer is not completed and data is not complete */
	else
	{
		return BufferNotCompletedDataCompleted;
	}
}

//************************************************************************
//						Bootloader_WitrePage
//
//	Function Description    : Write data buffer onto flash page
//	Parameter in			: PageAddress: Address of Page
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Buffer: Pointer to data buffer
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//************************************************************************
void Bootloader_WitrePage (uint32_t PageAddress, uint8_t *Buffer)
{
	uint16_t ui8Count;

	/* Disable interrupts */
	Disable_Interrupts();

	/* Wait until EEPROM finish work if there is any */
	eeprom_busy_wait ();

	/* Erase page from flash */
	boot_page_erase (PageAddress);

	/* Wait until the memory is erased */
	boot_spm_busy_wait ();

	for (ui8Count = 0; ui8Count < SPM_PAGESIZE; ui8Count += 2)
	{
		// Set up little-endian word.

		uint16_t Word = *Buffer++;
		Word += (*Buffer++) << 8;

		boot_page_fill (PageAddress + ui8Count, Word);
	}

	boot_page_write (PageAddress);     // Store buffer in flash page.
	boot_spm_busy_wait();       // Wait until the memory is written.

	// Reenable RWW-section again. We need this if we want to jump back
	// to the application after bootloading.

	boot_rww_enable ();

	// Re-enable interrupts (if they were ever enabled).

	Enable_Interrupts();
}

//************************************************************************
//						String_To_IHex
//
//	Function Description    : Converts ASCII frame to Intel Hex frame
//	Parameter in			: none
//	Parameter inout         : ASCII_Frame: Pointer to ASCII frame
//	Parameter out           : none
//	Return value            : IHex_Frame: Intel Hex frame
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//************************************************************************
IHex_Frame String_To_IHex(uint8* ASCII_Frame)
{
	/* Intel Hex frame */
	IHex_Frame IHexFrame;

	/* Counters */
	uint8 ui8count = 0;

#if(STD_ON == BOOTLOADER_CHECKSUM)
	/* Value of check sum */
	uint8 ui8CheckSumValue = 0;
#endif

	/* Initiate IHex frame */
	IHexFrame.valid = FALSE;

	/* Byte count is two hex digits ( 1 & 2 ) */
	IHexFrame.byte_count = (ASCII_To_HEX(ASCII_Frame[1]) << 4) | ASCII_To_HEX(ASCII_Frame[2]);

	/* First Hex digit must be colon */
	if(ASCII_Frame[0] != ':')
	{
		return IHexFrame;
	}

	/* Numbers of characters in frame must be byte count + 11 (data length) */
	else if(string_length(ASCII_Frame) < (IHexFrame.byte_count + 11))
	{
		return IHexFrame;
	}

	else{}

	/* Convert ASCII to Hex */
	for(ui8count = 1; ui8count < string_length(ASCII_Frame); ui8count++)
	{
		if(ASCII_To_HEX(ASCII_Frame[ui8count]) > 0xFF){
			return IHexFrame;
		}
	}

	/* Address is four digits ( 3 & 4 & 5 & 6 ) */
	IHexFrame.address = (ASCII_To_HEX(ASCII_Frame[3]) << 12) | (ASCII_To_HEX(ASCII_Frame[4]) << 8) | (ASCII_To_HEX(ASCII_Frame[5]) << 4) | ASCII_To_HEX(ASCII_Frame[6]);

	/* The physical address of the data is computed by adding this offset to a previously established base address */
	IHexFrame.address |= (AddressOffset << 4);

	/* Record is two digits ( 7 & 8 ) */
	IHexFrame.record_type = (ASCII_To_HEX(ASCII_Frame[7]) << 4) | ASCII_To_HEX(ASCII_Frame[8]);


#if(STD_ON == BOOTLOADER_CHECKSUM)
	/* Checksum is the last two digits  */
	IHexFrame.checksum = (ASCII_To_HEX(ASCII_Frame[IHexFrame.byte_count] + 9) << 4) | ASCII_To_HEX(ASCII_Frame[IHexFrame.byte_count] + 10);

	/* Calculating value of check sum */
	ui8CheckSumValue = IHexFrame.byte_count + IHexFrame.record_type + (IHexFrame.address >> 8) + (IHexFrame.address & 0xFF);
#endif

	for(ui8count = 0; ui8count < IHexFrame.byte_count; ui8count++)
	{
		IHexFrame.data[ui8count] = (ASCII_To_HEX(ASCII_Frame[ui8count*2 + 9]) << 4) | ASCII_To_HEX(ASCII_Frame[ui8count*2 + 10]);

#if(STD_ON == BOOTLOADER_CHECKSUM)

		/* Calculating value of check sum */
		ui8CheckSumValue += IHexFrame.data[ui8count];
#endif
	}

#if(STD_ON == BOOTLOADER_CHECKSUM)

	/*A record's checksum byte is the two's complement of the least significant byte (LSB) of the sum of all decoded byte values
	  in the record preceding the checksum. It is computed by summing the decoded byte values and extracting the LSB of the sum
	  (i.e., the data checksum), and then calculating the two's complement of the LSB */

	ui8CheckSumValue &= 0b11;
	ui8CheckSumValue = (~ui8CheckSumValue) + 1;

	if(ui8CheckSumValue != IHexFrame.checksum){
		return IHexFrame;
	}
#endif

	/* Frame is valid */
	IHexFrame.valid = TRUE;

	return IHexFrame;
}


uint8 ASCII_To_HEX(uint8 ASCII)
{
	/* Function to convert ASCII letter to Hex digit */

	if((ASCII >= '0') && (ASCII <= '9'))
	{
		return ASCII - '0';
	}
	else if((ASCII >= 'A') && (ASCII <= 'F'))
	{
		return ASCII - 'A' + 10;
	}
	else if((ASCII >= 'a') && (ASCII <= 'f'))
	{
		return ASCII - 'a' + 10;
	}
	else
	{
		return 255;
	}
}

uint8 string_length(uint8 str[])
{
	/* Function to get the length of string */

	uint8 count;
	/* count the string start from element 0 until the element before the NULL terminator */
	for(count = 0; str[count] != '\0'; ++count);
	return count;
}
