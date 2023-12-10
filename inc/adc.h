/*
 * adc.h
 *
 *  Created on: 02.06.2023
 *      Author: franzweunsche
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32f7xx.h"

#define ADC_ADC_ON		(1U<<0)
#define ADC_ContConv	(1U<<1)		//ADC_CR2 Bit 1 controls Continuous mode
#define ADC_SeqLen_1	0
#define ADC_CH4_SQ1		(1U<<2)		// 0b 0100 = 1U<<2 = 4 aka Channel 4
									// Channel 12 would be 0b 1100 = 3U << 2
#define ADC_StartConv	(1U<30)		//ADC_CR2 Bit 30 controls software conversion start
#define ADC_EOC_Flag	(1U<<1)		//ADC_SR End of Conversion Flag
#define ADC_EOC_IE		(1U<<5)		//ADC_CR1 EOCIE


uint32_t adc_read (ADC_TypeDef * ADCx);
void PA4_adc1_Init(void);
void PA4_adc1__Interrupt_Init(void);

#endif /* ADC_H_ */
