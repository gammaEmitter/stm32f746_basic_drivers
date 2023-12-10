/*
 * i2c.c
 *
 *  Created on: 15.06.2023
 *      Author: franzweunsche
 */

#include "i2c.h"

//slave
void i2c2_config(void) {



	//config SCL and SDA GPIO Pins PB10 (SCL) and PB11 (SDA)

	set_AHB1_periph_clk(GPIO_B_EN);

	gpio_set_pin_mode(GPIOB, I2C2_SCL, GPIO_ALT_MODE);
	gpio_set_pin_af(GPIOB,I2C2_SCL,GPIO_AF4_AFR);
	gpio_set_pin_outtype(GPIOB, I2C2_SCL, OpenDrain);
	gpio_set_pin_pullmode(GPIOB, I2C2_SCL, PullUp);

	gpio_set_pin_mode(GPIOB, I2C2_SDA, GPIO_ALT_MODE);
	gpio_set_pin_af(GPIOB,I2C2_SDA,GPIO_AF4_AFR);
	gpio_set_pin_outtype(GPIOB, I2C2_SDA, OpenDrain);
	gpio_set_pin_pullmode(GPIOB, I2C2_SDA, PullUp);

	set_APB1_periph_clk(I2C2_CLK_EN);

	NVIC_EnableIRQ(I2C2_EV_IRQn);
	i2c_set_adress(I2C2, I2C_SLAVE_OWNADRESS, AdressMode_7bit);

	i2c_enable_interrupts(I2C2, I2C_CR1_ADDRIE | I2C_CR1_STOPIE | I2C_CR1_NACKIE);


}




//master
void i2c1_config(void) {


	//config SCL PB6 SDA PB9

	set_AHB1_periph_clk(GPIO_B_EN);

	gpio_set_pin_mode(GPIOB, I2C1_SCL, GPIO_ALT_MODE);
	gpio_set_pin_af(GPIOB,I2C1_SCL,GPIO_AF4_AFR);
	gpio_set_pin_outtype(GPIOB, I2C1_SCL, OpenDrain);
	gpio_set_pin_pullmode(GPIOB, I2C1_SCL, PullUp);

	gpio_set_pin_mode(GPIOB, I2C1_SDA, GPIO_ALT_MODE);
	gpio_set_pin_af(GPIOB,I2C1_SDA,GPIO_AF4_AFR);
	gpio_set_pin_outtype(GPIOB, I2C1_SDA, OpenDrain);
	gpio_set_pin_pullmode(GPIOB, I2C1_SDA, PullUp);

	set_APB1_periph_clk(I2C1_CLK_EN);



	//i2c_set_adress(I2C1, I2C_SLAVE_OWNADRESS, AdressMode_7bit);
	i2c_set_timing(I2C2, I2C_TIMING);
	//master works in polling mode, slave in interrupt mode --> interrupts in master not enabled
	//i2c_enable_interrupts(I2C2, I2C_CR1_ADDRIE | I2C_CR1_STOPIE | I2C_CR1_NACKIE);



}



void i2c_set_adress (I2C_TypeDef * I2Cx, uint32_t OwnAdress ,I2C_AddressMode AddressSize) {
	CLEAR_BIT(I2Cx->CR1,I2C_CR1_PE);
	MODIFY_REG(I2Cx->OAR1, I2C_OAR1_OA1 | I2C_OAR1_OA1MODE, OwnAdress | AddressSize);
	SET_BIT(I2Cx->OAR1, I2C_OAR1_OA1EN);
	SET_BIT(I2Cx->CR1,I2C_CR1_PE);
}

void i2c_enable_interrupts(I2C_TypeDef * I2Cx, uint32_t Interrupts) {
	SET_BIT(I2Cx->CR1, Interrupts);
}

void i2c_set_timing (I2C_TypeDef * I2Cx, uint32_t Timing) {
	CLEAR_BIT(I2Cx->CR1,I2C_CR1_PE);
	SET_BIT(I2Cx->TIMINGR, Timing);
	SET_BIT(I2Cx->CR1,I2C_CR1_PE);
}

uint32_t i2c_get_addresscode (I2C_TypeDef * I2Cx) { // get content of I2C_ISR_ADDCODE register
	return (uint32_t)(READ_BIT(I2Cx->ISR, I2C_ISR_ADDCODE) >> I2C_ISR_ADDCODE_Pos << 1);
}

