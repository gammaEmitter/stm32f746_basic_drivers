/*
 * gpio.c
 *
 *  Created on: Jun 1, 2023
 *      Author: franzweunsche
 */
#include "gpio.h"
#include <stdio.h>



void gpio_set_pin_mode (GPIO_TypeDef* GPIOx, uint32_t PinNumber, uint32_t Mode) {
	/*
	 * CLEARMASK 0b 11 (Alternate Function, bit ) << Bit 20 (two digits occupy bit 16 and 17 thus
	 *			 0b 11 == 0x3
	 *
	 * */
	MODIFY_REG(GPIOx->MODER, 0x3 << (POSITION_VAL(PinNumber)*2U), Mode << (POSITION_VAL(PinNumber)*2U));

}

void gpio_set_pin_af(GPIO_TypeDef* GPIOx, uint32_t PinNumber, uint32_t AlternatingFunction) {
	if (POSITION_VAL(PinNumber) <= 7) {
		MODIFY_REG(GPIOx->AFR[0], 0xF << (POSITION_VAL(PinNumber) * sizeof(uint32_t)), AlternatingFunction << (POSITION_VAL(PinNumber)) * sizeof(uint32_t));
	} else {
		MODIFY_REG(GPIOx->AFR[1], 0xF << ((POSITION_VAL(PinNumber) - 8) * (sizeof(uint32_t))), AlternatingFunction << ((POSITION_VAL(PinNumber) - 8) * (sizeof(uint32_t)))); //if fails try ( * 4) instead of (* sizeof(uint32_t))
	}
}

void gpio_usr_btn_init(void) {
	set_AHB1_periph_clk(GPIO_I_EN);
	gpio_set_pin_mode(GPIOI, USR_BTN, GPIO_IN_MODE);

//	GPIOI->MODER &=~ (1U<<22);
//	GPIOI->MODER &=~ (1U<<23);
}

void usr_btn_polling() {

	if (GPIOI->IDR & USR_BTN) { // Button pressed
		LED_On();
		printf("User Button Pressed\n");
	} else {
		LED_Off();
	}
}

void gpio_set_pin_outspeed(GPIO_TypeDef* GPIOx, uint32_t PinNumber, GPIO_OutputSpeed Speed) {
	MODIFY_REG(GPIOx->OSPEEDR, 0x3 << (POSITION_VAL(PinNumber)*2U), Speed << (POSITION_VAL(PinNumber)*2U));
}
void gpio_set_pin_pullmode(GPIO_TypeDef* GPIOx, uint32_t PinNumber, GPIO_PullMode PullMode) {
	MODIFY_REG(GPIOx->PUPDR, 0x3 << (POSITION_VAL(PinNumber)*2U), PullMode << (POSITION_VAL(PinNumber)*2U));
}

void gpio_set_pin_outtype(GPIO_TypeDef* GPIOx, uint32_t PinNumber, GPIO_OutputType Type) {
	SET_BIT(GPIOx->OTYPER, Type << POSITION_VAL(PinNumber));
}
