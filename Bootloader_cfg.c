/*
 * Bootloader_cfg.c
 *
 *  Created on: 25 Feb 2020
 *      Author: Yahia
 */

#include "Bootloader.h"

/* Boot-loader configuration struct */
Bootloader_ConfigType Bootloader_ConfigTypeContainer =
{
		BOOTLOADER_AppProtection,
		BOOTLOADER_BootloaderProtection,
		BOOTLOADER_BootResetAddress,
		BOOTLOADER_BootSizeConfiguration,
		BOOTLOADER_BootAfterReset,
		BOOTLOADER_ReadWhileWriting,
		BOOTLOADER_InterruptMode
};
