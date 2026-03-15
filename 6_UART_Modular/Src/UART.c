/*
 * UART.c
 *
 *  Created on: Jan 27, 2024
 *      Author: VAMSI KRISHNA
 */

#include "UART.h"
#include <stdint.h>


/* ***** STATIC FUNCTION PROTOTYPES ***** */
static uint16_t UART_Compute_Div(uint32_t PeriphClk, uint32_t Baudrate);
static void UART_BaudRate_Config(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static void UART2_Write(USART_TypeDef* USARTx, uint8_t ch);


/* Special Function - Print characters  */
int __io_putchar(int ch)
{
	UART2_Write(USART2, ch);
	return ch;
}


/* ***** FUNCTION DEFINITIONS ***** */

/* Function 1 - UART 2 Transmission Initialization */
void UART2_Tx_Init(void)
{
	/* **** LOW-LEVEL GPIO CONFIGURATION **** */

	/* ** Configure PA2 - TX line ** */
	// 1. Enable clock access to GPIO-A for PA2 as TX line
	RCC->AHB2ENR |= GPIO_A_EN;

	// 2. Configure PA2 mode to alternate function mode
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	// 3. Configure the alternate function to UART
	GPIOA->AFR[0]|= (1U<<8);
	GPIOA->AFR[0]|= (1U<<9);
	GPIOA->AFR[0]|= (1U<<10);
	GPIOA->AFR[0]&=~(1U<<11);

	/* ************************************** */


	/* **** UART 2 MODULE CONFIGURATION **** */
	// 1. Enable clock access to UART 2 module
	RCC->APB1ENR1 |= UART_2_EN;

	// 2. Configure the baud rate
		// i)  Compute the UART divider for the required baud rate
		// ii) Set the baud rate after the divider value is calculated
			   UART_BaudRate_Config(USART2, APB1_CLK, 115200);

	// 3. Configure the transfer direction
	USART2->CR1	   = (1U<<3); //RESETTING THE PREVIOUS VALUES (Hence, the entire register is reset except TE bit)

	// 4. Enable the UART 2 module
	USART2->CR1	  |= (1U<<0);

	/* ************************************* */
}


/* Function 2 - UART Divider for baud rate */
static uint16_t UART_Compute_Div(uint32_t PeriphClk, uint32_t Baudrate)
{
	// Returns the clock divider value based on the Peripheral clock and the required baud rate
	return ((PeriphClk + (Baudrate/2)) / Baudrate );
}


/* Function 3 - Configure the required baud rate for UART */
static void UART_BaudRate_Config(USART_TypeDef* USARTx, uint32_t PeriphClk, uint32_t Baudrate)
{
	// Configures the UART with the required baud rate
	USARTx->BRR = UART_Compute_Div (PeriphClk, Baudrate);
}


/* Function 4 - UART Write  */
static void UART2_Write(USART_TypeDef* USARTx, uint8_t ch)
{
	// Wait for the transmit data register to be empty before sending the new byte of data
	while(!(USARTx->ISR & (1U<<7)))
	{

	}

	// Transmit the data
	USARTx->TDR = ch & 0xFF; // Ensures that all 8 bits are transferred if the databyte is sparse
}

