#include "clock.h"

volatile uint32_t tick;

void CLOCK_INIT(void)
{
	//Enable HSE and configure clock to run on max 84 MHz
	FLASH->ACR |= (5 << FLASH_ACR_LATENCY_Pos);
	RCC->CR |= RCC_CR_HSEON;
		while(!(RCC->CR & RCC_CR_HSERDY)){} // wait for HSE to be stable
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ;
	RCC->PLLCFGR |= 7 << RCC_PLLCFGR_PLLQ_Pos;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR |= 80 << RCC_PLLCFGR_PLLN_Pos;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
	RCC->PLLCFGR |= 4 << RCC_PLLCFGR_PLLM_Pos;
	RCC->CR |= RCC_CR_PLLON;
		while(!(RCC->CR & RCC_CR_PLLRDY)){} // wait for PLL to lock	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
		while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)){}
		
	SysTick_Config(SystemCoreClock / 1000);	
	
}

void delay_ms(uint32_t ms)
{
	tick = 0;
	while(tick < ms);
}

void SysTick_Handler(void)
{
tick++;
}

