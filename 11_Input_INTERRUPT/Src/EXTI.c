/*
 * EXTI.c
 *
 *  Created on: Jan 29, 2024
 *      Author: VAMSI KRISHNA
 */


#include "stm32l4xx.h"

/* ***** FUNCTION DEFINITIONS ***** */
/* Function 1 - User Button (PC13) GPIO-EXTI mode initialization */
void UserBtn_PC13_EXTI_Init(void)
{
	// 1. Enable clock access to GPIO-C
	RCC->AHB2ENR |= (1U<<2); 	// Set bit2  is for GPIO-C

	// 2. Enable clock access to SYSCFG (to trigger interrupts)
	RCC->APB2ENR	 |= (1U<<0); 	// Set bit0 is for SYSCFG

	// 3. Configure PC13 as input pin
	GPIOC->MODER &=~(1U<<26); 	// Clear bits 26 and 27 to configure pin 13 in input mode
	GPIOC->MODER &=~(1U<<27);

	// 4. Configure the EXTI for PC13
		// i)   Clear (Reset) port selection for PC13
		SYSCFG->EXTICR[3] &=~(1U<<4);	// Clear bits 4 to 7 from the EXTICR[3] register for pin 13
		SYSCFG->EXTICR[3] &=~(1U<<5);
		SYSCFG->EXTICR[3] &=~(1U<<6);
		SYSCFG->EXTICR[3] &=~(1U<<7);

		// ii)  Select GPIO-C for EXTI13
		SYSCFG->EXTICR[3] |= (1U<<5);	// Set bit5 only for GPIO-C

		// iii) Unmask  EXTI13 in the interrupt mask register of NVIC
		EXTI->IMR1		  |= (1U<<13);	// Set bit13 for pin 13

		// iv)  Select the edge trigger (Rising/Falling edge) : Falling edge trigger selected here
		EXTI->FTSR1		  |= (1U<<13);  // Set bit 13 for falling edge on pin 13

		// v)	Finally, enable the EXTI line in NVIC
		NVIC_EnableIRQ(EXTI15_10_IRQn); // Interrupts from line 10-15 are muxed and hence we are calling its IRQ number to enble it

}
