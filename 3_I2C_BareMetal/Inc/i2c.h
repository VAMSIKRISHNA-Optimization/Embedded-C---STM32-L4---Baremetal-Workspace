/*
 * i2c.h
 *
 *  Created on: Jan 26, 2024
 *      Author: VAMSI KRISHNA
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32l4xx.h"

#define SLAVE_OWN_ADDRESS		0x5A


void I2C1_SlaveConfiguration  (void);
void I2C3_MasterConfiguration (void);

#endif /* I2C_H_ */
