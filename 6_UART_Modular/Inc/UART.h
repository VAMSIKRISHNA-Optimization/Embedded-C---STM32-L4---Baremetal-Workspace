/*
 * UART.h
 *
 *  Created on: Jan 27, 2024
 *      Author: VAMSI KRISHNA
 */

#ifndef UART_H_
#define UART_H_

#include "stm32l4xx.h"


/* ***** #defines ***** */
#define GPIO_A_EN		(1U<<0)
#define UART_2_EN		(1U<<17)

#define SYS_FREQ		4000000
#define APB1_CLK		SYS_FREQ


/* ***** FUNCTION PROTOTYPES ***** */
void UART2_Tx_Init(void);

#endif /* UART_H_ */
