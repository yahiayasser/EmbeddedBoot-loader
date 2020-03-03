/*
 * Interrupts.c
 *
 *  Created on: 27 Feb 2020
 *      Author: Yahia
 */
#include"Interrupts.h"

boolean InterruptIsAlreadyDisabled_Flag = FALSE;
uint8 InterruptDontEnable_Count = 0;

void Disable_Interrupts(void)
{
	if(False == InterruptIsAlreadyDisabled_Flag)
	{
		/*	If the interrupts is not disabled by another function, we 		*/
		/*	should disable it. and set the InterruptIsAlreadyDisabled_Flag	*/

		cli();
		InterruptIsAlreadyDisabled_Flag = TRUE;
	}
	else
	{
		/*	If the interrupts is disabled by another function, we should	        */
		/*	only increment the InterruptDontEnable_Count to prevent this function	*/
		/*	from enabling the interrupt										        */

		InterruptDontEnable_Count++;
	}
}

void Enable_Interrupts(void){

	/* Check the InterruptDontEnable_Count to determine if we should enable the interrupt or not */
	if(InterruptDontEnable_Count)
	{
		/* Decrement InterruptDontEnable_Count flag without enabling interrupts */
		InterruptDontEnable_Count--;
	}
	else
	{
		/* Reset InterruptIsAlreadyDisabled_Flag flag and enable interrupts */
		sei();
		InterruptIsAlreadyDisabled_Flag = FALSE;
	}
}
