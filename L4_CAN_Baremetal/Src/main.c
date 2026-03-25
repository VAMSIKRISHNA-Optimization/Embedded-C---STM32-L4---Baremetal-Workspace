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

#include <stdint.h>
#include "stm32l451xx.h"

int main(void)
{
    /* Loop forever */
	RCC->AHB2ENR |= (1U<<0);
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	for(;;)
	{
		GPIOA->ODR ^= (1U<<5);

		for(uint32_t i = 0; i<100000; i++);


	}
}
