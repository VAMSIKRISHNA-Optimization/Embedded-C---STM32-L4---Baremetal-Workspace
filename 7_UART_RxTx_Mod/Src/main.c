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

#include "UART.h"

/* ***** #defines ***** */
#define PIN_5		(1U<<5)
#define LED_PIN		PIN_5
#define GPIOAEN		(1U<<0)


/* ***** GLOBAL VARIABLES ***** */
char rcvd_data;


/* ***** MAIN FUNCTION ***** */
int main(void)
{

	// Initialize the LED GPIO
	RCC  ->AHB2ENR |= GPIOAEN;

	GPIOA->MODER   |= (1U<<10);
	GPIOA->MODER   &=~(1U<<11);

	// Initialize the UART in Tx and Rx mode
	UART2_RxTx_Init();

    /* Loop forever */
	for(;;)
	{
		rcvd_data = UART2_Read(USART2);

		if (rcvd_data == '1')
		{
			GPIOA ->ODR |= LED_PIN;
		}
		else
		{
			GPIOA ->ODR &=~LED_PIN;
		}

	}

}

