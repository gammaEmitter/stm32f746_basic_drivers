/*
 * rcc.c
 *
 *  Created on: Jun 1, 2023
 *      Author: franzweunsche
 */
#include "rcc.h"

void set_AHB1_periph_clk (uint32_t periph) {

	SET_BIT(RCC->AHB1ENR, periph);
}
void set_AHB2_periph_clk (uint32_t periph) {

	SET_BIT(RCC->AHB2ENR, periph);
}
void set_APB1_periph_clk (uint32_t periph) {

	SET_BIT(RCC->APB1ENR, periph);
}
void set_APB2_periph_clk (uint32_t periph) {

	SET_BIT(RCC->APB2ENR, periph);
}

