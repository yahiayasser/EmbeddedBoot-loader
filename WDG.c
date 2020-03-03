/*
 * WDG.c
 *
 *  Created on: 20 Feb 2020
 *      Author: Yahia
 */

#include "Platform_Types.h"
#include "common_macros.h"
#include "micro_config.h"
#include "WDG.h"

void WDG_Init(void)
{
	/* Write logical one to WDTOE and WDE */
	WDTCR |= (1<<WDTOE) | (1<<WDE);

	/* Minimum time for reset */
	WDTCR &= ~(1<<WDP2);
	WDTCR &= ~(1<<WDP1);
	WDTCR &= ~(1<<WDP0);
}

void WDG_Reset(void)
{
	for(;;);
}
