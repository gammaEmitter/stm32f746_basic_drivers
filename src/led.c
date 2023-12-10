/*
 * led.c
 *
 *  Created on: Jun 1, 2023
 *      Author: franzweunsche
 */

/*
 *  STM32F746G-Disco    LED1 = LED_Green = PI1
 *
 *
 * */

#include "led.h"
#include "gpio.h"
#include "rcc.h"

void LED_Init(void) {
	set_AHB1_periph_clk(GPIO_I_EN);
	gpio_set_pin_mode(GPIOI, LED1_Pin, GPIO_OUT_MODE);

}

void LED_On(void) {
	GPIOI->BSRR = LED1_Pin;
}

void LED_Off(void) {
	GPIOI->BSRR = LED1_Pin_Off;

}
void LED_Toggle(void) {
	GPIOI->ODR ^= LED1_Pin;


}
