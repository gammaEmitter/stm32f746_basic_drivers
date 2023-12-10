/*
 * gpio.h
 *
 *  Created on: Jun 1, 2023
 *      Author: franzweunsche
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f7xx.h"
#include "rcc.h"
#include "led.h"

// AHB1 CLK Enable
#define GPIO_A_EN			(1U<<0)
#define GPIO_B_EN			(1U<<1)
#define GPIO_C_EN			(1U<<2)
#define GPIO_D_EN			(1U<<3)
#define GPIO_G_EN			(1U<<6)
#define GPIO_I_EN			(1U<<8)

// Pin definitions
#define USART3_TX			(1U<<8)		// Pin Numbers
#define USART1_TX			(1U<<9)
#define USART1_RX			(1U<<7)
#define USART2_TX			(1U<<2)
#define USART6_TX			(1U<<14)

#define USR_BTN				(1U<<11)		//Button B1 on Port I Pin 11
#define ADC_1_2_IN_CH4		(1U<<4)
#define SPI1_SCK			(1U<<5)
#define SPI1_MOSI			(1U<<7)			//Master is MOSI, Slave is MISO
#define SPI3_SCK			(1U<<10)
#define SPI3_MISO			(1U<<11)




#define GPIO_ALT_MODE		(0x2) //0b 10 see doc
#define GPIO_OUT_MODE		(0x1) //0b 01 see doc
#define GPIO_IN_MODE		(0x0)
#define GPIO_ANALOGUE_MODE	(0x3) // 0b 11
#define GPIO_AF7_AFR		(0x7)
#define GPIO_AF6_AFR		(0x6)
#define GPIO_AF5_AFR		(0x5)
#define GPIO_AF4_AFR		(0x4)
#define GPIO_AF10_AFR		(0x10)

typedef enum {
	Low = 					(0x0),
	Medium = 				(0x1),
	High = 					(0x2),
	VeryHigh = 				(0x3)
} GPIO_OutputSpeed;

typedef enum {
	NoPullUpNoPullDown = 	(0x0),
	PullUp = 				(0x1),
	PullDown =				(0x2)
} GPIO_PullMode;

typedef enum {
	PushPull =				(0x0),
	OpenDrain =				(0x1)
} GPIO_OutputType;

void gpio_set_pin_mode (GPIO_TypeDef* GPIOx, uint32_t PinNumber, uint32_t Mode);
void gpio_set_pin_af(GPIO_TypeDef* GPIOx, uint32_t PinNumber, uint32_t AlternatingFunction);
void gpio_usr_btn_init(void);
void usr_btn_polling(void);
void gpio_set_pin_outspeed(GPIO_TypeDef* GPIOx, uint32_t PinNumber, GPIO_OutputSpeed Speed);
void gpio_set_pin_pullmode(GPIO_TypeDef* GPIOx, uint32_t PinNumber, GPIO_PullMode Speed);
void gpio_set_pin_outtype(GPIO_TypeDef* GPIOx, uint32_t PinNumber, GPIO_OutputType Type);


#endif /* GPIO_H_ */
