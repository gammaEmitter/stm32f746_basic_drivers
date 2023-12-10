/*
 * led.h
 *
 *  Created on: Jun 1, 2023
 *      Author: franzweunsche
 */



#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define LED1_Pin			(1U<<1)
#define LED1_Pin_Off		(1U<<17)

void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);

#endif /* LED_H_ */
