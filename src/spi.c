/*
 * spi.c
 *
 *  Created on: Jun 8, 2023
 *      Author: franzweunsche
 */

#include "spi.h"


void spi1_config(void) {


	// SCK GPIO Pin PA5
	set_AHB1_periph_clk(GPIO_A_EN);
	gpio_set_pin_mode(GPIOA, SPI1_SCK,GPIO_ALT_MODE);
	gpio_set_pin_af(GPIOA,SPI1_SCK,GPIO_AF5_AFR);
	gpio_set_pin_outspeed(GPIOA,SPI1_SCK,VeryHigh);
	gpio_set_pin_pullmode(GPIOA,SPI1_SCK,PullDown);
	// SPI1 MOSI Pin ... Master Out Slave In    PA7
	gpio_set_pin_mode(GPIOA, SPI1_MOSI,GPIO_ALT_MODE);
	gpio_set_pin_af(GPIOA,SPI1_MOSI,GPIO_AF5_AFR);
	gpio_set_pin_outspeed(GPIOA,SPI1_MOSI,VeryHigh);
	gpio_set_pin_pullmode(GPIOA,SPI1_MOSI,PullDown);

	NVIC_EnableIRQ(SPI1_IRQn);

	set_APB2_periph_clk(SPI1_CLK_EN);

	spi_set_baudrate(SPI1, _256); //1 APB2 Cock Divider
	spi_set_bidirection(SPI1, OneLineBidirectional, OutputEnabled);
	spi_set_clock(SPI1, Polarity180, PhaseSecond);
	spi_set_datasize (SPI1, _8bit);
	spi_set_ssm(SPI1, SSM_Enabled);
	spi_set_sso(SPI1, SSO_Enabled);
	spi_set_threshold(SPI1, Fifo8bit);
	spi_tx_interrupt_enable(SPI1, SPI_TXE_Enabled);
	spi_set_type(SPI1, SPI_Master);



}

void spi3_config (void) {
	// SCK GPIO Pin PC10 (alt PB3)
	set_AHB1_periph_clk(GPIO_C_EN);
	gpio_set_pin_mode(GPIOC, SPI3_SCK,GPIO_ALT_MODE);
	gpio_set_pin_af(GPIOC,SPI3_SCK,GPIO_AF6_AFR);
	gpio_set_pin_outspeed(GPIOC,SPI3_SCK,VeryHigh);
	gpio_set_pin_pullmode(GPIOC,SPI3_SCK,PullDown);
	// SPI3 MOSI Pin ... Master Out Slave In    PC11 (alt PB4
	gpio_set_pin_mode(GPIOC, SPI3_MISO,GPIO_ALT_MODE);
	gpio_set_pin_af(GPIOC,SPI3_MISO,GPIO_AF6_AFR);
	gpio_set_pin_outspeed(GPIOC,SPI3_MISO,VeryHigh);
	gpio_set_pin_pullmode(GPIOC,SPI3_MISO,PullDown);

	NVIC_EnableIRQ(SPI3_IRQn);

	set_APB1_periph_clk(SPI3_CLK_EN);

	spi_set_baudrate(SPI3, _256); //1 APB1 Cock Divider
	spi_set_bidirection(SPI3, OneLineBidirectional, OutputDisabled); //Output Disabled == RX Line == Slave
	spi_set_clock(SPI3, Polarity180, PhaseSecond);
	spi_set_datasize (SPI3, _8bit);
	spi_set_ssm(SPI3, SSM_Enabled);
	spi_set_sso(SPI3, SSO_Enabled);
	spi_set_threshold(SPI3, Fifo8bit);
	spi_rx_interrupt_enable(SPI3, SPI_RXNE_Enabled);
	spi_set_type(SPI3, SPI_Slave);



}

void spi_set_baudrate(SPI_TypeDef * SPIx, SPI_Baudrate Divider) {
	MODIFY_REG(SPIx->CR1, 0x7 << 3, Divider << 3);
}

void spi_set_bidirection (SPI_TypeDef * SPIx, SPI_BiDiMode DirectionMode, SPI_BiDiOutput OutputMode) {
	SET_BIT(SPIx->CR1, DirectionMode << 15);
	SET_BIT(SPIx->CR1, OutputMode << 14);
}

void spi_set_clock (SPI_TypeDef * SPIx,SPI_ClockPolarity Polarity, SPI_ClockPhase Phase) {
	SET_BIT(SPIx->CR1, Polarity << 1);
	SET_BIT(SPIx->CR1, Phase << 0);
}

void spi_set_datasize(SPI_TypeDef * SPIx, SPI_DataSize BitLength) {
	MODIFY_REG(SPIx->CR2,0xF << 8, BitLength << 8);
}

void spi_set_ssm(SPI_TypeDef * SPIx, SPI_SSlaveManagement SSMMode) {
	SET_BIT(SPIx->CR1, SSMMode << 9);
}

void spi_tx_interrupt_enable(SPI_TypeDef * SPIx, SPI_TXIEnable TXI_Mode) {
	SET_BIT(SPIx->CR2, TXI_Mode << 7);
}

void spi_rx_interrupt_enable(SPI_TypeDef * SPIx, SPI_RXIEnable RXI_Mode) {
	SET_BIT(SPIx->CR2, RXI_Mode << 6);
}

void spi_set_sso(SPI_TypeDef * SPIx, SPI_SlaveSelOutput SSOEnable) {
	SET_BIT(SPIx->CR2, SSOEnable << 2);
}

void spi_set_threshold(SPI_TypeDef * SPIx, SPI_FifoThreshold FifoReceptionThreshold) {
	SET_BIT(SPIx->CR2, FifoReceptionThreshold << 12);
}

void spi_set_type(SPI_TypeDef * SPIx, SPI_MasterSlaveSelect Type ) {
	SET_BIT(SPIx->CR1, Type << 2);
}

//currently only spi1 and spi3 pre-baked working, TODO generalise config functions
void spi_master_slave_enable(SPI_TypeDef * Master, SPI_TypeDef * Slave) {
	SET_BIT(Slave->CR1, (1 << 6));
	SET_BIT(Master->CR1, (1 << 6));
}
