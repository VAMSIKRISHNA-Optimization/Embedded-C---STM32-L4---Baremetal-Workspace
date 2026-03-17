/*
 * SysTick.c
 *
 *  Created on: Jan 27, 2024
 *      Author: VAMSI KRISHNA
 */
#include "stm32l4xx.h"
#include "SysTick.h"


/* ***** Function Definitions ***** */
/* Function 1 - SYSTICK delay in ms */
void SYS_Delay_ms(uint32_t delay)
{
	// 1. Reload the Systick with number of cycles per milliseconds
	SysTick->LOAD  = SYSTICK_ms_LoadVal;

	// 2. Clear Systick's current value register
	SysTick->VAL   = 0;

	// 3. Select the clock source for Systick
	SysTick ->CTRL |= ST_CTRL_CLKSRC;

	// 4. Enable Systick
	SysTick ->CTRL |= ST_CTRL_ENABLE;

	// 5. Wait until the required delay elapses
	for(uint32_t i=0; i<delay; i++)
	{
		// Wait until the count flag in the Systick is set
		while((SysTick->CTRL & ST_CTRL_COUNTFLAG) == 0)
		{

		}
	}

	// 6. Reset the Systick's control register for next use
	SysTick ->CTRL  = 0;


}
