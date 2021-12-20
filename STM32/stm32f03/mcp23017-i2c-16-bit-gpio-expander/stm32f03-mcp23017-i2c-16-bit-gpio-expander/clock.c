#include "clock.h"

volatile uint32_t tick;

void delay_ms(uint32_t ms)
{
	tick = 0;
	while(tick < ms);
}

void SysTick_Handler(void)
{
tick++;
}
