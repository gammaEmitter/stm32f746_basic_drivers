/*
 * rcc.h
 *
 *  Created on: Jun 1, 2023
 *      Author: franzweunsche
 */

#ifndef RCC_H_
#define RCC_H_

#include "stm32f7xx.h"

#define USART3_CLK_EN		(1U<<18)
#define USART1_CLK_EN		(1U<<4) 		//APB2ENR Register Bit 4
#define USART6_CLK_EN		(1U<<5) 		//APB2ENR Register Bit 5
#define USART2_CLK_EN		(1U<<17)

#define ADC1_CLK_EN			(1U<<8)

#define SPI1_CLK_EN			(1U<<12)		//APB2
#define SPI3_CLK_EN			(1U<<15)		//APB1


void set_AHB1_periph_clk (uint32_t periph);
void set_AHB2_periph_clk (uint32_t periph);
void set_APB1_periph_clk (uint32_t periph);
void set_APB2_periph_clk (uint32_t periph);

#endif /* RCC_H_ */
