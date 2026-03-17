/*
 * ADC.c
 *
 *  Created on: Jan 27, 2024
 *      Author: VAMSI KRISHNA
 */

#include "ADC.h"

/* ***** FUNCTION DEFINITIONS ***** */
/* Function 1 - ADC 1 Single-ended mode Initialization */
void ADC1_Init(void)
{
	/* **** LOW-LEVEL GPIO CONFIGURATION **** */

	/* ** Configure PA4 - ADC Single-ended mode ** */
	// 1. Enable clock access to GPIO-A for PA4 as ADC input
	RCC->AHB2ENR |= GPIO_A_EN;

	// 2. Configure PA4 mode to analog mode
	GPIOA->MODER |= (1U<<8);
	GPIOA->MODER |= (1U<<9);

	// 3. Connect GPIO analog switch to ADC input (Exclusive to L47 series MCUs only)
	// Not applicable to L452

	/* ************************************** */


	/* **** ADC 1 MODULE CONFIGURATION **** */
	// 1. Enable clock access to ADC 1 module
	RCC->AHB2ENR |= ADC_EN;

	// 2. Configure the common clock for the ADC module (01:Sets the ADC clock to HCLK/2)
	ADC1_COMMON->CCR &=~(1U<<16);
	ADC1_COMMON->CCR |= (1U<<17);

	// 3. Configure continuous conversion mode
	ADC1->CFGR   |= (1U<<13);

	// 4. Set the length of the sequence (Specify the number of conversions in continuous mode, average of the conversions is given to user)
	ADC1->SQR1 = 0; //0 specifies 1 conversion

	// 5. Configure the ADC channel's properties and assign a rank for priority
		// Here 9th channel(it is the only one being used) must be put in SQ1 for rank of 1 (Use 9 in binary 01001)
		ADC1->SQR1 |= (1U<<6);
//		ADC1->SQR1 &=~(1U<<7);
//		ADC1->SQR1 &=~(1U<<8);
		ADC1->SQR1 |= (1U<<9);
//		ADC1->SQR1 &=~(1U<<10);

	// 6. Disable ADC deep power down (This is exclusive to low power series MCUs)
	ADC1->CR     &=~(1U<<29);

	// 7. Enable ADC's internal regulator (This is exclusive to low power series MCUs)
	ADC1->CR     |= (1U<<28);

	// 8. Start the ADC calibration
	ADC1->CR     |= (1U<<31);

	// 9. Finally, enable the ADC
	ADC1->CR     |= (1U<<0);


	/* ************************************* */
}


/* Function 2 - ADC 1 Start Conversion */
void ADC1_StartConversion(void)
{
	ADC1->CR     |= (1U<<2);
}

/* Function 3 - ADC 1 Get readings */
uint32_t ADC1_GetValue(void)
{
	// Wait for End-of-conversion flag to be set
	while(!(ADC1->ISR & (1U<<2)))
	{

	}

	// Clear the End-of-conversion flag once it has been set
	ADC1->ISR    |= (1U<<2);

	// Read the ADC value
	return ADC1->DR;
}
