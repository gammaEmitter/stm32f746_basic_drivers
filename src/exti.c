/*
 * exti.c
 *
 *  Created on: 05.06.2023
 *      Author: franzweunsche
 */

#include "exti.h"




void exti_user_button_init(void) {
	//gpio clock access ahb1 PI11
	//set PI11 to Input
	gpio_usr_btn_init();

	//enable clk access to SYSCFG module
	set_APB2_periph_clk(SYSCFG_CLK_EN);
	//clear port selection for EXTI - 11
	//select port I for EXTI11
	exti11_configure();


	//enable EXTI11 in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void exti11_configure(void) {
	// EXTI_CR3 --> 0b 1000 to bit [15:12]
//	SYSCFG->EXTICR[2] = 0x00000000; //explicitly reset register and set
//	SYSCFG->EXTICR[2] |= (8U << 12);
	SYSCFG->EXTICR[2] &=~ (1U<<12);
	SYSCFG->EXTICR[2] &=~ (1U<<13);
	SYSCFG->EXTICR[2] &=~ (1U<<14);
	SYSCFG->EXTICR[2] &=~ (1U<<15);

	SYSCFG->EXTICR[2] |= (1U<<15);

	//unmask EXTI11
	// Port I Pin 11 is on Line 11
	EXTI->IMR |= (1U<<11);

	//falling edge or rising edge interrupt trigger
	//EXTI->FTSR |= (1U<<11);
	//falling edge or rising edge interrupt trigger
	EXTI->RTSR |= (1U<<11);

}
