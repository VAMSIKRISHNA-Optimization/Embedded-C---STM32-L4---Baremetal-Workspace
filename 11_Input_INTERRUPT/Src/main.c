/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Vamsi Krishna
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include <stdio.h>
#include <stdint.h>

#include "EXTI.h"
#include "SysTick.h"
#include "UART.h"
#include "ADC.h"


/* ***** #defines ***** */
#define PIN_5		(1U<<5)
#define LED_PIN		PIN_5
#define GPIOAEN		(1U<<0)




/* ***** GLOBAL VARIABLES ***** */
int Sensor_Val;


/* ***** MAIN FUNCTION ***** */
int main(void)
{

	// Initialize the LED GPIO
	RCC  ->AHB2ENR |= GPIOAEN;

	GPIOA->MODER   |= (1U<<10);
	GPIOA->MODER   &=~(1U<<11);

	// Initialize UART to send data whenever interrupt occurs
	UART2_RxTx_Init ();

	// Initialize USER BUTTON (PC13) in interrupt mode
	UserBtn_PC13_EXTI_Init();





    /* Loop forever */
	for(;;)
	{


	}

}


/* ***** INTERRUPT HANDLERs ***** */
// GPIO PINS 10-15 IRQ HANDLER
void EXTI15_10_IRQHandler(void)
{
	// Check the EXTI's pending register to check if Pin13's interrupt has occurred
	if((EXTI->PR1 & GPIO_PIN13)!=0)
	{
		// 1. First clear the pending register (set it back to pending mode) to re-arm the trigger (in case if the interrupt triggers)
		//If the pending register is cleared, it will generate interrupts indefinitely for one trigger
		EXTI->PR1 |= GPIO_PIN13;

		// 2. Do something very short such as turning ON led or setting/clearing flag and do the other sub-critical part in the callback function
		// DO NOT USE DELAYS IN THE IRQ HANDLER
		GPIOA->ODR ^= LED_PIN;
		printf("BUTTON PRESSED\n\r");
	}


}
