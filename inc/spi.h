/*
 * spi.h
 *
 *  Created on: Jun 8, 2023
 *      Author: franzweunsche
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f7xx.h"

#include "gpio.h"
#include "rcc.h"
typedef enum {
	_2   = 				(0U<<3),
	_4   =				(1U<<0),
	_8	 =				(1U<<1),
	_16  = 				(3U<<0),
	_32  =				(1U<<2),
	_64	 =				(5U<<0),
	_128 =				(3U<<1),
	_256 =				(7U<<0)
} SPI_Baudrate;

typedef enum {
	TwoLineUnidirectional = (0x0),
	OneLineBidirectional  = (0x1)
} SPI_BiDiMode;

typedef enum {
	OutputDisabled 		  = (0x0),
	OutputEnabled		  = (0x1)
} SPI_BiDiOutput;

typedef enum {
	PolarityZero 		  = (0x0),
	Polarity180		  	  = (0x1)
} SPI_ClockPolarity;

typedef enum {
	PhaseFirst 		  = (0x0),
	PhaseSecond	  	  = (0x1)
} SPI_ClockPhase;

typedef enum {
	_4bit   = 				(3U<<0),
	_5bit  =				(1U<<2),
	_6bit	 =				(5U<<0),
	_7bit	 =				(3U<<1),
	_8bit  =				(7U<<0),
	_9bit	 =				(1U<<3),
	_10bit =				((1U<<3) | (1U <<0)),
	_114bit =				(5U<<1),
	_124bit =				((1U<<3) | (3U <<0)),
	_134bit =				(3U<<2),
	_144bit =				((3U<<2) | (1U <<0)),
	_154bit =				(7U<<1) ,
	_164bit =				((3U<<2) | (3U<<0))
} SPI_DataSize;

typedef enum {
	SSM_Enabled = 				(0x1),
	SSM_Disabled= 				(0x0)
} SPI_SSlaveManagement;

typedef enum {
	SSO_Enabled = 				(0x1),
	SSO_Disabled= 				(0x0)
} SPI_SlaveSelOutput;

typedef enum {
	Fifo16bit	=				(0x0),
	Fifo8bit	=				(0x1)
} SPI_FifoThreshold;

typedef enum {
	SPI_TXE_Enabled =			(0x1),
	SPI_TXE_Disabled =			(0x0)
} SPI_TXIEnable;

typedef enum {
	SPI_RXNE_Enabled =			(0x1),
	SPI_RXNE_Disabled =			(0x0)
} SPI_RXIEnable;

typedef enum {
	SPI_Master = 				(0x1),
	SPI_Slave  =				(0x0)
} SPI_MasterSlaveSelect;

//			SPI 1 as Master
// 			SPI 3 as Slave
void spi_set_baudrate(SPI_TypeDef * SPIx, SPI_Baudrate Divider);

void spi_set_bidirection (SPI_TypeDef * SPIx, SPI_BiDiMode DirectionMode, SPI_BiDiOutput OutputMode);

void spi_set_clock (SPI_TypeDef * SPIx,SPI_ClockPolarity Polarity,SPI_ClockPhase Phase);

void spi_set_datasize(SPI_TypeDef * SPIx, SPI_DataSize BitLength);

void spi_set_ssm(SPI_TypeDef * SPIx, SPI_SSlaveManagement SSMMode);

void spi_set_sso(SPI_TypeDef * SPIx, SPI_SlaveSelOutput SSOEnable);

void spi_set_threshold(SPI_TypeDef * SPIx, SPI_FifoThreshold FifoReceptionThreshold);

void spi_tx_interrupt_enable(SPI_TypeDef * SPIx, SPI_TXIEnable TXI_Mode);

void spi_rx_interrupt_enable(SPI_TypeDef * SPIx, SPI_RXIEnable RXI_Mode);

void spi_set_type(SPI_TypeDef * SPIx, SPI_MasterSlaveSelect Type );

void spi1_config(void);

void spi3_config(void);

void spi_master_slave_enable(SPI_TypeDef * Master, SPI_TypeDef * Slave);
/*
 * 	GPIO A 5,6,7,8 AF5
 *
 *
 * */

//			SPI 3

#endif /* SPI_H_ */
