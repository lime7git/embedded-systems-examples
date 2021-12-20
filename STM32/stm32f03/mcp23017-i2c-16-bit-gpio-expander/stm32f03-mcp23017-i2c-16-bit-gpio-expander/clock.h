#ifndef _CLOCK
#define _CLOCK
#include <stm32f030x8.h>
#include <stm32f0xx.h>

extern volatile uint32_t tick;

	void delay_ms(uint32_t ms);
	void SysTick_Handler(void);
#endif
