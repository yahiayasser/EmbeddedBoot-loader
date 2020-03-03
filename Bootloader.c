/*
 * Bootloader_prg.c
 *
 *  Created on: 20 Feb 2020
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

/* Bootloader_Flag is a flag that indicates if there is bootable program or not */
boolean Bootloader_Flag;

/* Structure that contains the configuration parameters of boot-loader */
extern Bootloader_ConfigType Bootloader_ConfigTypeContainer;



//************************************************************************
//						Bootloader
//
//	Function Description    : This function is responsible for writing the program
//							  into the flash.
//	Parameter in			: none
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//************************************************************************
void Bootloader(void)
{
/* This service allow a systems software to be updated without the use of specialized
   hardware such as a JTAG programmer, The boot-loader manages the systems images.
 * This service is also the earliest point at which the integrity of a system can be
   checked, it is automatically called after uC reset without user intervention.
 * This service can communicate over a variety of protocols such as USART, CAN, I2C, Ethernet,
   USB and the list goes on for as many protocols that exist, depending on the uC capabilities
   and user configuration.
 * This service must be updated with the use of specialized hardware such as a JTAG programmer
   or another boot-loader.
 * This service can parse different types of Hex files such as Intel HEX, Motorola S-Records
   and Raw Binary (In the mean time, it only accepts Intel HEX files).
*/

#if(ATMEGA32 != BOOTLOADER_TARGET)
#error "The SW version of Bootloader does not suppot this type of micro controller"
#endif

	/* Disable interrupts */
	Disable_Interrupts();

	/* Reset stack pointer to its initial value */
	ResetStackPointer;

#if(Intel_HEX == BOOTLOADER_FILE_FORMAT)

	/* IHex_Frame structure to hold the Hex value of the incoming IHex frame */
	IHex_Frame IHexFrame;

	/* StringFrame string to hold the ASCII value of the incoming IHex frame */
	uint8 StringFrame[MaxFrameLength];

	/* Counter */
	uint8 ui8Count = 0;

	/* DataBuffer array to hold data that will be written in the flash */
	uint8 DataBuffer[PageSizeB];

	/* Counter of DataBuffer array */
	uint8 DataBufferCounter;

	/* NextAddress is a pointer to the next page that will be written.
	 * Used to check if the writing process on the flash is continuous or not.
	 */
	uint32 NextAddress = NULL_Address;

	/* PageAddress holds the address value of page that will be written */
	uint32 PageAddress = 0x0;


	/*****************************************************/
	/*                  Branch section                   */
	/*****************************************************/
	if(FALSE == GetBootloaderFlag)
	{
		/* The branching code makes the decision as to whether the boot-loader is loaded
		   or whether the application is loaded.
		 * The branching code in this application is nothing more than checking flag value
		   that is stored in the EEPROM.
		 * If flag is set then there is an image that is waiting to be written, if it is
		  cleared then the reset is not because of boot-loader and the boot-loader
		  application has nothing to do and it must jump to the main application.
		 */

		/* Reset stack pointer to its initial value */
		ResetStackPointer;

		/* Enable interrupts */
		Enable_Interrupts();

		/* Jump to the main application (user application) */
		GoToApp;
	}


	/*****************************************************/
	/*          Boot-loader application section          */
	/*****************************************************/

	/* Initialise HW modules used by Boot-loader */
	Bootloader_HW_Init();

	while(1)
	{

		/* Initiate IHexFrame */
		IHexFrame.valid = FALSE;

		/* Trigger transmission */
		SendChar(IHexFrameStartTransmission);

		/* Receive IHex Frame in ASCII wise */
		for(ui8Count = 0; ui8Count < MaxFrameLength; ui8Count++)
		{
			StringFrame[ui8Count] = GetChar;
			if(StringFrame[ui8Count] == '\r')
			{
				StringFrame[ui8Count] = '\0';
				break;
			}
			else{}
		}

		/* Convert ASCII frame to Hex frame */
		IHexFrame = String_To_IHex(StringFrame);

		/* Frame validation test */
		if(TRUE != IHexFrame.valid)
		{
			/* If frame is not valid then retransmit, if valid then continue */

			/* Transmission failed */
			SendChar(BootloaderFrameNotSuccess);
		}
		else
		{
			/* Case 1	: Data is completely loaded into the data buffer and the buffer is not completed
			 * Workflow	: Do nothing
			 */
			if(Bootloader_LoadBuffer(&IHexFrame, DataBuffer, &DataBufferCounter, &NextAddress) == BufferNotCompletedDataCompleted)
			{
			}

			/* Case 2	: Data is completely loaded into the data buffer and the buffer is completed
			 * Workflow	: -Write buffer onto the flash
			 * 			  -Reset DataBufferCounter to start a new buffer
			 */
			else if(Bootloader_LoadBuffer(&IHexFrame, DataBuffer, &DataBufferCounter, &NextAddress) == BufferCompletedDataCompleted)
			{
				/* Reset DataBufferCounter */
				DataBufferCounter = 0;

				/* Write data buffer onto the flash */
				Bootloader_WitrePage(PageAddress, DataBuffer);

				/* Start a new page */
				PageAddress = NextAddress;
			}

			/* Case 3	: Data is not completely loaded into the data buffer as the buffer is completed
			 * Workflow	: -Write buffer onto the flash
			 * 			  -Reset DataBufferCounter to start a new buffer
			 * 			  -load the remaining data into new buffer
			 */
			else if(Bootloader_LoadBuffer(&IHexFrame, DataBuffer, &DataBufferCounter, &NextAddress) == BufferCompletedDataNotCompleted)
			{
				/* Write data buffer onto the flash */
				Bootloader_WitrePage(PageAddress, DataBuffer);

				/* New page address = frame address + number of written data */
				PageAddress = (IHexFrame.address) + DataBufferCounter;

				uint8 temp_count = DataBufferCounter;	//Counter on data buffer
				uint8 temp_index = 0;					//Index of data buffer

				/* Shift data that is not written yet to the start of the buffer */
				while(temp_count < (IHexFrame.byte_count))
				{
					IHexFrame.data[temp_index] = IHexFrame.data[temp_count];
					temp_index++;
					temp_count++;
				}

				/* byte_count = byte_count - number of written data */
				IHexFrame.byte_count = IHexFrame.byte_count - DataBufferCounter;

				/* Reset NextAddress */
				NextAddress = NextAddress - (IHexFrame.byte_count);

				/* Reset DataBufferCounter */
				DataBufferCounter = 0;

				/* load data into new buffer */
				Bootloader_LoadBuffer(&IHexFrame, DataBuffer, &DataBufferCounter, &NextAddress);
			}

			/* Case 4	: Data that should be written is not after the previous data
			 * Example	: Prev data address = 0x20
			 	 	 	  Prev data size = 0x10
			 	 	 	  Current data address = 0xA0
			 	 	 	  In the previous example the expected address of the new data is 0x30 (0x20 + 0x10), but the
			 	 	 	  address is 0xA0, that means that the new data is not sequentially after the previous data
			 * Workflow	: -Write old buffer onto the flash even if it is not completed
			 * 			  -Reset DataBufferCounter to start a new buffer
			 * 			  -load the data into new buffer
			 */
			else if(Bootloader_LoadBuffer(&IHexFrame, DataBuffer, &DataBufferCounter, &NextAddress) == BufferNotCompletedDataNotCompleted)
			{
				/* Reset DataBufferCounter */
				DataBufferCounter = 0;

				/* Write data buffer onto the flash*/
				Bootloader_WitrePage(PageAddress, DataBuffer);

				/* Update PageAddress to point to the current data address */
				PageAddress = NextAddress;

				/* load data into new buffer */
				Bootloader_LoadBuffer(&IHexFrame, DataBuffer, &DataBufferCounter, &NextAddress);
			}

			/* Case 5	: Data is successfully loaded into the flash and we reached the end of the file
			 * Workflow	: -Clear boot-loader flag from EEPROM
			 * 			  -Reset stack pointer to the point to the first address in the ram
			 * 			  -Enable interrupts
			 * 			  -Jump to the main application (user application)
			 */
			else
			{
				/* Finish transmission */
				SendChar(BootloaderFinish);

				/* Clear boot-loader flag from EEPROM */
				ClearBootloaderFlag;

				/* Clear boot-loader flag */
				Bootloader_Flag = FALSE;

				/* Reset stack pointer */
				ResetStackPointer;

				/* Enable interrupts */
				Enable_Interrupts();

				/* Jump to the main application (user application) */
				GoToApp;
			}

			/* Transmit new frame */
			SendChar(BootloaderFrameSuccess);
		}
	}

#elif(Motorola_S_Records == BOOTLOADER_FILE_FORMAT)
#error "The SW version of Bootloader does not suppot Motorola S-Records in the mean time"
#elif(Raw_Binary == BOOTLOADER_FILE_FORMAT)
#error "The SW version of Bootloader does not suppot Raw Binary in the mean time"
#else
#error "Undefined BOOTLOADER_FILE_FORMAT"
#endif

}

//************************************************************************
//						Bootloader_Runnable
//
//	Function Description    : Boot-loader main function
//	Parameter in			: none
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Sync/Async				: Asynchronous
//	Reentrancy				: Non reentrant
//************************************************************************
void Bootloader_Runnable(void)
{
	/* Check boot-loader flag */
	if(TRUE == Bootloader_Flag)
	{
		/* If Bootloader_Flag is set then reset uC
		 * If Bootloader_Flag is cleared then continue executing the program
		 */

		/* Set the value of Bootloader_Flag in the EEPROM */
		SetBootloaderFlag;

		/* Reset uC */
		MC_Reset();
	}
}

//************************************************************************
//						Bootloader_GetConfiguration
//
//	Function Description    : Get the configuration parameters of boot-loader
//	Parameter in			: none
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Bootloader_ConfigType -> Structure that contains
//							  the configuration parameters of boot-loader
//	Sync/Async				: Asynchronous
//	Reentrancy				: Non reentrant
//************************************************************************
Bootloader_ConfigType Bootloader_GetConfiguration(void)
{
	/* Return the structure that contains the configuration parameters of boot-loader */
	return Bootloader_ConfigTypeContainer;
}

//************************************************************************
//						Bootloader_Uninstall
//
//	Function Description    : Uninstall boot-loader section
//	Parameter in			: none
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//************************************************************************
void Bootloader_Uninstall(void)
{
	/* This API is used to uninstall and free the boot-loader section from the flash
	 * You should also set the value of BOOTRST in Fuses.h
	 */

	uint32 PageAddress = Bootloader_StartAddress;	// Start of boot-loader section

	/* Disable interrupts */
	Disable_Interrupts();

	while(PageAddress < Bootloader_EndAddress)
	{

		boot_page_erase(PageAddress);
		PageAddress += (FLASH_PageSize*2);
	}

	/* Enable interrupts */
	Enable_Interrupts();

	while(1);
}
