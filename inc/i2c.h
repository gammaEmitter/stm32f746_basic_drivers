/*
 * i2c.h
 *
 *  Created on: 15.06.2023
 *      Author: franzweunsche
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f7xx.h"
#include "gpio.h"
#include "rcc.h"

typedef enum {
	AdressMode_7bit = 		(0x0),
	AdressMode_10bit=		(0x1)
} I2C_AddressMode;

#define I2C2_CLK_EN			(1U<<22)
#define I2C1_CLK_EN			(1U<<21)

#define I2C2_SCL			(1U<<10)		//PB10 AF4 = I2C2 SCL
#define I2C2_SDA			(1U<<11)		//PB11 AF4 = I2C2 SCL
#define I2C1_SCL			(1U<<6)			//PB6
#define I2C1_SDA			(1U<<9)			//PB9

#define I2C_SLAVE_OWNADRESS	(0x5A) //ramdomly chosen ?!?
#define I2C_MASTER_OWNADRESS (0x5A) //ramdomly chosen ?!?

#define I2C_TIMING			(0x00303D5B)
#define I2C_DIRECTION_WRITE (0x00000000U)

//    I2C 1 Master (AHB1)
//	  I2C 2 Slave  (AHB2)

void i2c1_config(void);
void i2c2_config(void);

void i2c_set_adress (I2C_TypeDef * I2Cx, uint32_t OwnAdress ,I2C_AddressMode AddressSize);
void i2c_enable_interrupts(I2C_TypeDef * I2Cx, uint32_t Interrupts);
void i2c_set_timing (I2C_TypeDef * I2Cx, uint32_t Timing);
uint32_t i2c_get_addresscode (I2C_TypeDef * I2Cx);






#endif /* I2C_H_ */
