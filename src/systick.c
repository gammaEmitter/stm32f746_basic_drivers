#include "systick.h"

void Sys_Delay (uint32_t delay) {
	// reload the number of clocks per milisecond
	SysTick->LOAD = SYSTICK_1MS - 1;
	// clear the Current Value Register  SYST_CVR
	SysTick->VAL = 0;
	// select clock source and enable systick
	SysTick->CTRL = SYSTICK_ENABLE | SYSTICK_CLKSRC;

	for (int i = 0; i < delay; i++) {
		while ((SysTick->CTRL & SYSTICK_CLK_WF)==0) {} //stuck in while loop until 16000 cycles passed and clock wrapped around

	}
}

void Sys_Interrupt_Delay_Init(uint32_t rate) {
	// reload the number of clocks per milisecond
	SysTick->LOAD = (uint32_t)((SYSTICK_CORE_FREQ / rate) - 1);
	// clear the Current Value Register  SYST_CVR
	SysTick->VAL = 0;
	// select clock source and enable systick
	SysTick->CTRL = SYSTICK_ENABLE | SYSTICK_CLKSRC | SYSTICK_IRQ;

}
