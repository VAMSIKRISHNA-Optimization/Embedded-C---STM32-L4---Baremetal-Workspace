/*
 * i2c.c
 *
 *  Created on: Jan 26, 2024
 *      Author: VAMSI KRISHNA
 */

#include "i2c.h"

#define GPIOB_EN		(1U<<1)
#define GPIOC_EN		(1U<<2)

#define I2C1EN			(1U<<21)
#define I2C3EN			(1U<<23)

#define I2C1_TIMING		(0x00000E14)

//Function Prototypes
static void I2C1_SetSlaveAddress(uint32_t SlaveAddress, uint32_t SizeofSlaveAddress);


/*Functions for I2C */

//Function 1
void I2C1_SlaveConfiguration (void)
{
	/* ***** Low level configuration - GPIOs ***** */

	// SCL LINE - PB8 Configuration
	// Enable clock access to GPIO-B
		RCC->AHB2ENR |= GPIOB_EN;

	// Configure PB8 (SCL line) to alternate function mode
		GPIOB->MODER &=~(1U<<16);
		GPIOB->MODER |= (1U<<17);

	// Configure alternate function type to I2C1 (AF4)
		GPIOB->AFR[1] &=~(1U<<0);
		GPIOB->AFR[1] &=~(1U<<1);
		GPIOB->AFR[1] |= (1U<<2);
		GPIOB->AFR[1] &=~(1U<<3);

	// Configure PB8 pin in open-drain mode
		GPIOB->OTYPER |= (1U<<8);

	// Enable internal pull-up for PB8 pin
		GPIOB->PUPDR |= (1U<<16);
		GPIOB->PUPDR &=~(1U<<17);

	// SDA LINE - PB9 Configuration
	// Configure PB8 (SCL line) to alternate function mode
		GPIOB->MODER &=~(1U<<18);
		GPIOB->MODER |= (1U<<19);

	// Configure alternate function type to I2C1 (AF4)
		GPIOB->AFR[1] &=~(1U<<4);
		GPIOB->AFR[1] &=~(1U<<5);
		GPIOB->AFR[1] |= (1U<<6);
		GPIOB->AFR[1] &=~(1U<<7);

	// Configure PB9 pin in open-drain mode
		GPIOB->OTYPER |= (1U<<9);

	// Enable internal pull-up for PB9 pin
		GPIOB->PUPDR |= (1U<<18);
		GPIOB->PUPDR &=~(1U<<19);

	/* ******************************************* */



	/* ***** Communication device configuration - I2C ***** */

	// Enable clock access to I2C module
		RCC->APB1ENR1 |= I2C1EN;

	// Enable I2C interrupt in NVIC
		//NVIC_EnableIRQ(I2C1_EV_IRQn);

	// Pre-disbaling the I2C module to reconfigure in slave mode
		I2C1->CR1 &=~(1U<<0);

	// Set the slave address
		I2C1_SetSlaveAddress(SLAVE_OWN_ADDRESS, 0); //0 indicates 7-bit addressing mode

	// Enable the slave address ACKing (now own address)
		I2C1->OAR1 |= (1U<<15);

	// Enable I2C module
		I2C1->CR1 |= (1U<<0);

	// Enable ADDR interrupt

	// Enable NACK interrupt

	// Enable STOP interrupt

	/* **************************************************** */

}


//Function 2
static void I2C1_SetSlaveAddress(uint32_t SlaveAddress, uint32_t SizeofSlaveAddress)
{
	MODIFY_REG(I2C1->OAR1, I2C_OAR1_OA1 | I2C_OAR1_OA1MODE,  SlaveAddress | SizeofSlaveAddress);
}


//Function 3
void I2C3_MasterConfiguration (void)
{
	/* ***** Low level configuration - GPIOs ***** */

	// SCL LINE - PC0 Configuration
	// Enable clock access to GPIO-C
		RCC->AHB2ENR |= GPIOC_EN;

	// Configure PC0 (SCL line) to alternate function mode
		GPIOC->MODER &=~(1U<<0);
		GPIOC->MODER |= (1U<<1);

	// Configure alternate function type to I2C3 (AF4)
		GPIOC->AFR[0] &=~(1U<<0);
		GPIOC->AFR[0] &=~(1U<<1);
		GPIOC->AFR[0] |= (1U<<2);
		GPIOC->AFR[0] &=~(1U<<3);

	// Configure PC0 pin in open-drain mode
		GPIOC->OTYPER |= (1U<<0);

	// Enable internal pull-up for PC0 pin
		GPIOC->PUPDR |= (1U<<0);
		GPIOC->PUPDR &=~(1U<<1);

	// SDA LINE - PC1 Configuration
	// Configure PC1 (SCL line) to alternate function mode
		GPIOC->MODER &=~(1U<<2);
		GPIOC->MODER |= (1U<<3);

	// Configure alternate function type to I2C3 (AF4)
		GPIOC->AFR[0] &=~(1U<<4);
		GPIOC->AFR[0] &=~(1U<<5);
		GPIOC->AFR[0] |= (1U<<6);
		GPIOC->AFR[0] &=~(1U<<7);

	// Configure PB9 pin in open-drain mode
		GPIOC->OTYPER |= (1U<<1);

	// Enable internal pull-up for PB9 pin
		GPIOC->PUPDR |= (1U<<2);
		GPIOC->PUPDR &=~(1U<<3);

	/* ******************************************* */



	/* ***** Communication device configuration - I2C ***** */

	// Enable clock access to I2C module
		RCC->APB1ENR1 |= I2C3EN;

	// Enable I2C interrupt in NVIC
		//NVIC_EnableIRQ(I2C3_EV_IRQn);

	// Pre-disbaling the I2C module to reconfigure in master mode
		I2C3->CR1 &=~(1U<<0);

	// Set the timing for the master's clock (Standard/Fast mode - Get it from CubeMX)
		I2C3->TIMINGR = I2C1_TIMING;

	// Enable I2C module
		I2C3->CR1 |= (1U<<0);

	/* **************************************************** */

}
