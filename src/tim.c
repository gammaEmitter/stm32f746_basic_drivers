/*
 * tim.c
 *
 *  Created on: 03.06.2023
 *      Author: franzweunsche
 */

#include "tim.h"
#include "rcc.h"


//Timer 1 has only 16 bit ARR --> max value to compare for interrupt = 65535
void tim1_Init(uint32_t rate) {
	// enable clock
	set_APB2_periph_clk(TIM1_CLK_EN);
	//set prescaler
	TIM1->PSC = (1600 - 1);		// 16 000 000 / 1600 = 10 000
								// default system clock frequency divided by my set prescaler --> 10 000 Hz is the TIM1 frequency
	//set auto-reload value (timer length, timer threshold, period)
	TIM1->ARR = ((10000/rate) - 1); 	// TIM1 Freq / ARR-Value  --> 10 000 / 10 000 = 1 Hz

	//Enable TIM update interrupt
	TIM1->DIER |= TIM_UIE;		//Update Interrupt Enable


	//Enable TIM1 update interrupt in NVIC
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn); //Timer 1 and 10 Update Interrupt IRQ

	//enable timer
	TIM1->CR1 |= TIM_ENABLE;

	//Force update generation
	TIM1->EGR |= TIM_UG;

}

//Timer 2 has 32bit ARR --> can have Value for
void tim2_Init(uint32_t rate) {
	// enable clock
	set_APB1_periph_clk(TIM2_CLK_EN);
	//set prescaler
	TIM2->PSC = (16 - 1);		// 16 000 000 / 16 = 1 000 000
								// default system clock frequency divided by my set prescaler --> 1 000 000 Hz is the TIM2 frequency
	//set auto-reload value (timer length, timer threshold)
	TIM2->ARR = ((1000000/rate) - 1); 	// TIM2 Freq / ARR-Value  --> 1 000 000 / 1 000 000 = 1 Hz

	//Enable TIM update interrupt
	TIM2->DIER |= TIM_UIE;		//Update Interrupt Enable

	//Enable TIM1 update interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn); //Timer 2 IRQ

	//enable timer
	TIM2->CR1 |= TIM_ENABLE;

	//Force update generation
	TIM2->EGR |= TIM_UG;
}

//clear Update Interrupt Flag
void tim_clear_UIF (TIM_TypeDef * TIMx) {
	TIMx->SR &=~ TIM_SR_UIF;
}

// return true if Update Interrupt Flag is set --> ARR has overflown (up DIRection) or underflown (down DIRection)
bool tim_UIF_set (TIM_TypeDef * TIMx) {
	return (TIMx->SR & TIM_SR_UIF);
}
