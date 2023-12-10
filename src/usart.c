/*
 * usart.c
 *
 *  Created on: May 29, 2023
 *      Author: franzweunsche
 */
#include "usart.h"
#include "gpio.h"
#include "rcc.h"



void usart_write(USART_TypeDef* USARTx, uint8_t value) {
	/* make sure transmit data register is empty
	 * USART_TXE (bit 7 in USART_ISR Register) shows empty status of transmit data register
	 * write value into transmit data register
	*/
	while (!((USARTx->ISR & USART_ISR_TXE))) {}  // stuck in loop until Transmit Data Register Empty Bit is set to 1 (true, empty)

	//when its empty, send it
	USARTx->TDR = value;

}

uint8_t usart_read(USART_TypeDef* USARTx) {

	while (!((USARTx->ISR & USART_ISR_RXNE))) {} // Read Data Register Not Emptry

	return (READ_BIT(USARTx->RDR, USART_RDR_RDR) & 0xFFU); // 0xFF --> 0b 1111 1111 --> & operator tells to only return 8 bit, because only least significant 8 1s are turned to 1
}
int __io_putchar(int ch){
	usart_write(USART1, ch);
	return ch;
}


void usart_config_parameters(USART_TypeDef* USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits) {
	MODIFY_REG(USARTx->CR1, USART_CR1_PS | USART_CR1_PCE | USART_CR1_M, Parity | DataWidth);
	MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}

uint16_t usart_compute_div (uint32_t PeriphClk, uint32_t BaudRate){
	return (PeriphClk + (BaudRate/2U))/BaudRate;
}

void usart_set_baudrate(USART_TypeDef* USARTx,uint32_t PeriphClk, uint32_t BaudRate) {
	USARTx->BRR = usart_compute_div(PeriphClk, BaudRate);
}

void usart_set_direction(USART_TypeDef* USARTx, uint32_t Direction){
	MODIFY_REG(USARTx->CR1, USART_CR1_RE | USART_CR1_TE, Direction);
}

void usart_enable (USART_TypeDef* USARTx) {
	SET_BIT(USARTx->CR1, USART_CR1_UE);
}

void USART3_TX_Init() {
	// Enable CLK GPIOB (USART3 is connected to GPIO B Pin 10...
	//Set GPIOB Pin 10 to alternate function mode


	set_AHB1_periph_clk(GPIO_D_EN);
	gpio_set_pin_mode(GPIOD, USART3_TX, GPIO_ALT_MODE);





	//Set alternate function to USART

	//Modify Function takes clearmask of 4 bit = 1111  to clear all fields that are marked by 1
//	GPIOB->AFR[1] |= (1U<<8); //0b 0111 at bit 8 (to 11) for AF7 --> Alternate Function Mapping --> USART3_TX lies in AF7 column
//	GPIOB->AFR[1] |= (1U<<9);
//	GPIOB->AFR[1] |= (1U<<10);		 //0   1   1   1
//	GPIOB->AFR[1] &=~(1U<<11); 	//Bit  11  10  9   8


	//AF Register 10 Function AF7 (USART3 to GPIO Pin 10)


	gpio_set_pin_af(GPIOD, USART3_TX, GPIO_AF7_AFR); // should be same as the commented block above



	//Enable CLK to USART3 Module
	set_APB1_periph_clk(USART3_CLK_EN);


	//Configure USART Parameters
	usart_config_parameters(USART3, USART_DATAWIDTH_8B, USART_PARITY_NONE, USART_STOPBITS_1);
	//Set Direction to TX (TE = Transmission Enable
	usart_set_direction(USART3, USART_CR1_TE);
	//Set Baudrate
	usart_set_baudrate(USART3, 16000000, 115200);



	//Enable USART3
	usart_enable(USART3);

}

void USART1_TX_Init() {
	// Enable CLK GPIOB (USART3 is connected to GPIO B Pin 10...
		//Set GPIOB Pin 10 to alternate function mode


		set_AHB1_periph_clk(GPIO_A_EN);
		gpio_set_pin_mode(GPIOA, USART1_TX, GPIO_ALT_MODE);





		//Set alternate function to USART

		//Modify Function takes clearmask of 4 bit = 1111  to clear all fields that are marked by 1
	//	GPIOB->AFR[1] |= (1U<<8); //0b 0111 at bit 8 (to 11) for AF7 --> Alternate Function Mapping --> USART3_TX lies in AF7 column
	//	GPIOB->AFR[1] |= (1U<<9);
	//	GPIOB->AFR[1] |= (1U<<10);		 //0   1   1   1
	//	GPIOB->AFR[1] &=~(1U<<11); 	//Bit  11  10  9   8


		//AF Register 10 Function AF7 (USART3 to GPIO Pin 10)
//			GPIOA->AFR[1] |= (1U<<4); //0b 0111 at bit 8 (to 11) for AF7 --> Alternate Function Mapping --> USART3_TX lies in AF7 column
//			GPIOA->AFR[1] |= (1U<<5);
//			GPIOA->AFR[1] |= (1U<<6);		 //0   1   1   1
//			GPIOA->AFR[1] &=~(1U<<7); 	//Bit  11  10  9   8

		gpio_set_pin_af(GPIOA, USART1_TX, GPIO_AF7_AFR); // should be same as the commented block above



		//Enable CLK to USART3 Module
		set_APB2_periph_clk(USART1_CLK_EN);


		//Configure USART Parameters
		usart_config_parameters(USART1, USART_DATAWIDTH_8B, USART_PARITY_NONE, USART_STOPBITS_1);
		//Set Direction to TX (TE = Transmission Enable
		usart_set_direction(USART1, USART_CR1_TE);
		//Set Baudrate
		usart_set_baudrate(USART1, 16000000, 9600);



		//Enable USART3
		usart_enable(USART1);

}


void USART2_TX_Init() {
	// Enable CLK GPIOB (USART2 is connected to GPIO A 3
		//Set GPIOA 3 to alternate function mode


		set_AHB1_periph_clk(GPIO_A_EN);
		gpio_set_pin_mode(GPIOA, USART2_TX, GPIO_ALT_MODE);





		//Set alternate function to USART

		//Modify Function takes clearmask of 4 bit = 1111  to clear all fields that are marked by 1
	//	GPIOB->AFR[1] |= (1U<<8); //0b 0111 at bit 8 (to 11) for AF7 --> Alternate Function Mapping --> USART3_TX lies in AF7 column
	//	GPIOB->AFR[1] |= (1U<<9);
	//	GPIOB->AFR[1] |= (1U<<10);		 //0   1   1   1
	//	GPIOB->AFR[1] &=~(1U<<11); 	//Bit  11  10  9   8


		//AF Register 10 Function AF7 (USART3 to GPIO Pin 10)


		gpio_set_pin_af(GPIOA, USART2_TX, GPIO_AF7_AFR); // should be same as the commented block above



		//Enable CLK to USART3 Module
		set_APB1_periph_clk(USART2_CLK_EN);


		//Configure USART Parameters
		usart_config_parameters(USART2, USART_DATAWIDTH_8B, USART_PARITY_NONE, USART_STOPBITS_1);
		//Set Direction to TX (TE = Transmission Enable
		usart_set_direction(USART2, USART_CR1_TE);
		//Set Baudrate
		usart_set_baudrate(USART2, 16000000, 115200);



		//Enable USART3
		usart_enable(USART2);

}

void USART6_TX_Init() {
	// Enable CLK GPIOB (USART3 is connected to GPIO B Pin 10...
		//Set GPIOB Pin 10 to alternate function mode


		set_AHB1_periph_clk(GPIO_G_EN);
		gpio_set_pin_mode(GPIOG, USART6_TX, GPIO_ALT_MODE);





		//Set alternate function to USART

		//Modify Function takes clearmask of 4 bit = 1111  to clear all fields that are marked by 1
	//	GPIOB->AFR[1] |= (1U<<8); //0b 0111 at bit 8 (to 11) for AF7 --> Alternate Function Mapping --> USART3_TX lies in AF7 column
	//	GPIOB->AFR[1] |= (1U<<9);
	//	GPIOB->AFR[1] |= (1U<<10);		 //0   1   1   1
	//	GPIOB->AFR[1] &=~(1U<<11); 	//Bit  11  10  9   8


		//AF Register 10 Function AF7 (USART3 to GPIO Pin 10)


		gpio_set_pin_af(GPIOG, USART6_TX, GPIO_AF7_AFR); // should be same as the commented block above



		//Enable CLK to USART3 Module
		set_APB2_periph_clk(USART6_CLK_EN);


		//Configure USART Parameters
		usart_config_parameters(USART6, USART_DATAWIDTH_8B, USART_PARITY_NONE, USART_STOPBITS_1);
		//Set Direction to TX (TE = Transmission Enable
		usart_set_direction(USART6, USART_CR1_TE);
		//Set Baudrate
		usart_set_baudrate(USART6, 216000000, 115200);



		//Enable USART3
		usart_enable(USART6);

}




void USART1_RXTX_Init(InterruptFlag interrupt_state) {
	// Enable CLK GPIOB (USART3 is connected to GPIO B Pin 10...
		//Set GPIOB Pin 10 to alternate function mode

		/* USART1_TX = PA9
		 *
		 * USART1_RX = PB7
		 */


		set_AHB1_periph_clk(GPIO_A_EN);
		set_AHB1_periph_clk(GPIO_B_EN);
		gpio_set_pin_mode(GPIOA, USART1_TX, GPIO_ALT_MODE);
		gpio_set_pin_mode(GPIOB, USART1_RX, GPIO_ALT_MODE);





		//Set alternate function to USART

		//AF Register 10 Function AF7 (USART3 to GPIO Pin 10)
//			GPIOA->AFR[1] |= (1U<<4); //0b 0111 at bit 8 (to 11) for AF7 --> Alternate Function Mapping --> USART3_TX lies in AF7 column
//			GPIOA->AFR[1] |= (1U<<5);
//			GPIOA->AFR[1] |= (1U<<6);		 //0   1   1   1
//			GPIOA->AFR[1] &=~(1U<<7); 	//Bit  11  10  9   8

		gpio_set_pin_af(GPIOA, USART1_TX, GPIO_AF7_AFR); // should be same as the commented block above
		gpio_set_pin_af(GPIOB, USART1_RX, GPIO_AF7_AFR); // should be same as the commented block above


		//Enable CLK to USART3 Module
		set_APB2_periph_clk(USART1_CLK_EN);


		//Configure USART Parameters
		usart_config_parameters(USART1, USART_DATAWIDTH_8B, USART_PARITY_NONE, USART_STOPBITS_1);
		//Set Direction to TX (TE = Transmission Enable
		usart_set_direction(USART1, (USART_CR1_TE | USART_CR1_RE));
		//Set Baudrate
		usart_set_baudrate(USART1, 16000000, 9600);

		if (interrupt_state) {
			USART1->CR1 |= USART_CR1_TXEIE;
		}



		//Enable USART3
		usart_enable(USART1);

		//Enable NVIC
		if (interrupt_state) {
			NVIC_EnableIRQ(USART1_IRQn);
		}



}
