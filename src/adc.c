/*
 * adc.c
 *
 *  Created on: 02.06.2023
 *      Author: franzweunsche
 */

#include "adc.h"
#include "gpio.h"
#include "rcc.h"

// Pin PA4 = ADC1 and ADC2 Input Channel 4
void PA4_adc1_Init(void) {

	/* configure ADC GPIO Pin
	 *  - CLK Access GPIO A
	 *  - set PA4 to analog mode
	 * */
	set_AHB1_periph_clk(GPIO_A_EN);
	gpio_set_pin_mode(GPIOA, ADC_1_2_IN_CH4, GPIO_ANALOGUE_MODE);

	/* configure ADC Module
	 *  - CLK Access ADC 1 Module
	 *  - configure ADC 1 parameters --> set conversion to continous
	 *  - set sequencer length (single channel --> length 1)
	 *  - set channel to sample from
	 *  - enable ADC 1 Module
	 *  - start conversion
	 * */
	set_APB2_periph_clk(ADC1_CLK_EN);

	ADC1->CR2 |= ADC_ContConv;
	ADC1->SQR1 = ADC_SeqLen_1;

	// set channel 4 to sample rank 1 --> SQ1 in SQR3
	ADC1->SQR3 |= ADC_CH4_SQ1;

	ADC1->CR2 |= ADC_ADC_ON;

	ADC1->CR2 |= ADC_StartConv;


}
void PA4_adc1_Interrupt_Init(void) {

	/* configure ADC GPIO Pin
	 *  - CLK Access GPIO A
	 *  - set PA4 to analog mode
	 * */
	set_AHB1_periph_clk(GPIO_A_EN);
	gpio_set_pin_mode(GPIOA, ADC_1_2_IN_CH4, GPIO_ANALOGUE_MODE);

	/* configure ADC Module
	 *  - CLK Access ADC 1 Module
	 *  - configure ADC 1 parameters --> set conversion to continous
	 *  - set sequencer length (single channel --> length 1)
	 *  - set channel to sample from
	 *  - enable ADC 1 Module
	 *  - start conversion
	 * */
	set_APB2_periph_clk(ADC1_CLK_EN);

	ADC1->CR2 |= ADC_ContConv;
	ADC1->SQR1 = ADC_SeqLen_1;

	// set channel 4 to sample rank 1 --> SQ1 in SQR3
	ADC1->SQR3 |= ADC_CH4_SQ1;

	ADC1->CR2 |= ADC_ADC_ON;

	ADC1->CR1 |= ADC_EOC_IE;

	NVIC_EnableIRQ(ADC_IRQn);

	ADC1->CR2 |= ADC_StartConv;


}

uint32_t adc_read (ADC_TypeDef * ADCx) {
	/*
	 * - wait for conversion End of Conversion Flag
	 * - read result
	 *
	 * */

	// alternativly use falsed while loop to wait for Flag to set true
	if (ADCx->SR & ADC_EOC_Flag) {
		return (ADCx->DR);
	}
	return 0;

}



