/*
 * tim.h
 *
 *  Created on: 03.06.2023
 *      Author: franzweunsche
 */

#ifndef TIM_H_
#define TIM_H_

#include "stm32f7xx.h"
#include <stdint.h>
#include <stdbool.h>


#define TIM1_CLK_EN		(1U<<0)
#define TIM2_CLK_EN		(1U<<0)

#define TIM_ENABLE		(1U<<0)		//TIMx_CR1_CEN, valid for TIM1/8 aswell as TIM2/3/4/5/6/7
#define CR1_CEN			TIM_ENABLE

#define TIM_UIE			(1U<<0)		// Update Interrupt Enable
#define TIM_UG			(1U<<0)		// Update Generate

#define TIM1_UIF		(1U<<0)		//TIMx_SR Update Interrupt Flag
									// when TIMx_ARR is wrapped around, UIF is set
#define TIM2_UIF		(1U<<0)		//TIMx_SR Update Interrupt Flag
									// when TIMx_ARR is wrapped around, UIF is set


void tim1_Init(uint32_t rate);
void tim2_Init(uint32_t rate);
void tim_clear_UIF (TIM_TypeDef * TIMx);
bool tim_UIF_set (TIM_TypeDef * TIMx);


#endif /* TIM_H_ */
