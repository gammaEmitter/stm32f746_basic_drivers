/*
 * usart.h
 *
 *  Created on: May 29, 2023
 *      Author: franzweunsche
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f7xx.h"
#include <stdio.h>
#include <stdbool.h>

typedef enum  {
    InterruptEnable = true,
    InterruptDisable = false
} InterruptFlag;


#define USART_DATAWIDTH_8B  (0x00000000U)   //8 Bit wordlength: Start Bit, 8 bits data, stop bit
#define USART_PARITY_NONE   (0x00000000U)
#define USART_STOPBITS_1    (0x00000000U)   //ref manual: 00 = 1 stopbit

#define USART_TXEIE         (1U<<7)         //Interrupt when ISR_TXE = 1 --> Register empty, space for new data to be transmitted


void set_AHB1_periph_clk (uint32_t periph);

void set_APB1_periph_clk (uint32_t periph);
void set_APB2_periph_clk (uint32_t periph);
void usart_config_parameters(USART_TypeDef* USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits);
void usart_set_baudrate(USART_TypeDef* USARTx,uint32_t PeriphClk, uint32_t BaudRate);
uint16_t usart_compute_div (uint32_t PeriphClk, uint32_t BaudRate);
void usart_enable (USART_TypeDef* USARTx);
void usart_write(USART_TypeDef* USARTx, uint8_t value);
uint8_t usart_read(USART_TypeDef* USARTx);
void usart_set_direction(USART_TypeDef* USARTx, uint32_t Direction);
void USART3_TX_Init();
void USART1_TX_Init();
void USART2_TX_Init();
void USART6_TX_Init();
void USART1_RXTX_Init(InterruptFlag interrupt_enable);
#endif /* USART_H_ */
