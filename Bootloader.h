/*
 * Bootloader.h
 *
 *  Created on: 20 Feb 2020
 *      Author: Yahia
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#include "Compiler.h"
#include "Platform_Types.h"

/* Module Version 1.0.0 */
#define BOOTLOADER_SW_MAJOR_VERSION           (1U)
#define BOOTLOADER_SW_MINOR_VERSION           (0U)
#define BOOTLOADER_SW_PATCH_VERSION           (0U)

#include "Bootloader_dependencies.h"
/* Checking between Bootloader and Bootloader_dependencies Modules */
#if ((BOOTLOADER_SW_MAJOR_VERSION != BOOTLOADER_DEPENDENCIES_SW_MAJOR_VERSION)\
 ||  (BOOTLOADER_SW_MINOR_VERSION != BOOTLOADER_DEPENDENCIES_SW_MINOR_VERSION)\
 ||  (BOOTLOADER_SW_PATCH_VERSION != BOOTLOADER_DEPENDENCIES_SW_PATCH_VERSION))
  #error "The SW version of Bootloader_dependencies.h does not match the expected version"
#endif

#include "Abstraction.h"
#include"Interrupts.h"

#include "Bootloader_interface.h"
/* Checking between Bootloader and Bootloader_interface Modules */
#if ((BOOTLOADER_SW_MAJOR_VERSION != BOOTLOADER_INTERFACE_SW_MAJOR_VERSION)\
 ||  (BOOTLOADER_SW_MINOR_VERSION != BOOTLOADER_INTERFACE_SW_MINOR_VERSION)\
 ||  (BOOTLOADER_SW_PATCH_VERSION != BOOTLOADER_INTERFACE_SW_PATCH_VERSION))
  #error "The SW version of Bootloader_interface.h does not match the expected version"
#endif
#include "Bootloader_cfg.h"
/* Checking between Bootloader and Bootloader_cfg Modules */
#if ((BOOTLOADER_SW_MAJOR_VERSION != BOOTLOADER_CFG_SW_MAJOR_VERSION)\
 ||  (BOOTLOADER_SW_MINOR_VERSION != BOOTLOADER_CFG_SW_MINOR_VERSION)\
 ||  (BOOTLOADER_SW_PATCH_VERSION != BOOTLOADER_CFG_SW_PATCH_VERSION))
  #error "The SW version of Bootloader_cfg.h does not match the expected version"
#endif



#endif /* BOOTLOADER_H_ */
