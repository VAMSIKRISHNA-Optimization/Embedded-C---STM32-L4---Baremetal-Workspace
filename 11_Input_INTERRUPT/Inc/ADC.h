/*
 * ADC.h
 *
 *  Created on: Jan 27, 2024
 *      Author: VAMSI KRISHNA
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32l4xx.h"


/* ***** #defines ***** */
#define GPIO_A_EN		(1U<<0)
#define ADC_EN			(1U<<13)


/* ***** FUNCTION PROTOTYPES ***** */
void ADC1_Init(void);
void ADC1_StartConversion(void);
uint32_t ADC1_GetValue(void);


#endif /* ADC_H_ */
