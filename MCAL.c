/*
 * MCAL.c
 *
 *  Created on: 20 Feb 2020
 *      Author: Yahia
 */


#include "Bootloader_dependencies.h"
#include "Abstraction.h"

void Bootloader_HW_Init(void)
{
	CommunicationInit;
}

void MC_Reset(void)
{
	WDG_Init();
	WDG_Reset();
}
