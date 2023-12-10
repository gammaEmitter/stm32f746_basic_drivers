/*
 * systick.h
 *
 *  Created on: 03.06.2023
 *      Author: franzweunsche
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*
 *
 * STM32F746G Systick Core Clock Frequenc: 16 000 000 Hz == 16 MHz
 *
 * */

#include "stm32f7xx.h"
#include <stdint.h>

#define SYSTICK_CORE_FREQ	16000000
#define SYSTICK_1MS			16000
#define SYSTICK_CLKSRC		(1U<<2) // 1 Processor 0 External Clock
#define SYSTICK_ENABLE		(1U<<0)
#define SYSTICK_IRQ			(1U<<1) // TICKINT Bit enable exeption requeest == IRQ
#define SYSTICK_CLK_WF		(1U<<16)// Flag, if Clock has wrapped to 0 since the last time this bit was read
//Delay in ms
void Sys_Delay (uint32_t delay);
//
void Sys_Interrupt_Delay_Init(uint32_t rate);


#endif /* SYSTICK_H_ */
