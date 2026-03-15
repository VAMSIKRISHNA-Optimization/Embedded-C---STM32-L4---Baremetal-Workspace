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


/* ***** GLOBAL VARIABLES ***** */



/* ***** MAIN FUNCTION ***** */
int main(void)
{

	UART2_Tx_Init();

    /* Loop forever */
	for(;;)
	{
		printf("TEST FOR UART using printf MODULAR......\n\r");

		for(int i=0; i<100000; i++);
	}

}

