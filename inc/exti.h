/*
 * exti.h
 *
 *  Created on: 05.06.2023
 *      Author: franzweunsche
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f7xx.h"
#include "gpio.h"

#define SYSCFG_CLK_EN		(1U<<14)

void exti_user_button_init(void);
void exti11_configure(void);

#endif /* EXTI_H_ */
