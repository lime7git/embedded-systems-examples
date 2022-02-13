#ifndef _CLOCK
#define _CLOCK
#include <stm32f401xe.h>
#include <stm32f4xx.h>

extern volatile uint32_t tick;

	void CLOCK_INIT(void);
	void delay_ms(uint32_t ms);
	void SysTick_Handler(void);

#endif
