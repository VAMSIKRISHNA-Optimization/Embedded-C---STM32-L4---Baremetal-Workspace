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

	// Initialize UART to transmit ADC data over UART
	UART2_RxTx_Init();

	// Initialize ADC1 in single-ended mode
	ADC1_Init();

	// Add a bit of delay here
	int x;
	for(int i=0; i<100000; i++)
	{
		x++;
	}

	// Start the ADC1 conversion
	ADC1_StartConversion();

    /* Loop forever */
	for(;;)
	{
		Sensor_Val = ADC1_GetValue();

		for(int i=0; i<100000; i++);

		printf("Sensor Value = %d\n\r", Sensor_Val);

		if (Sensor_Val > 4000)
		{
			GPIOA ->ODR |= LED_PIN;
		}
		else
		{
			GPIOA ->ODR &=~LED_PIN;
		}

	}

}

