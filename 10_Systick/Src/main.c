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

	// Initialize UART to transmit  data over UART
	UART2_RxTx_Init();


    /* Loop forever */
	for(;;)
	{
		SYS_Delay_ms(1000);
		printf("A second just passed\n\r");
		GPIOA->ODR ^= LED_PIN;
	}

}

