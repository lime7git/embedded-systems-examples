#include "gpio.h"

void GPIO_INIT(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;	// taktowanie portu C
	
	
	GPIOC->MODER &= ~GPIO_MODER_MODER13;	// ustawienie pinu 13 jako cyfrowe wyjscie 
	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;	// taktowanie portu B
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	GPIOB->MODER &= ~GPIO_MODER_MODER0;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB;
	EXTI->IMR |= EXTI_IMR_IM0;
	EXTI->FTSR |= EXTI_FTSR_FT0;
	EXTI->RTSR |= EXTI_RTSR_RT0;
	NVIC_EnableIRQ(EXTI0_1_IRQn);

}
	
void LED_SWITCH(eGPIO_STATE state)
{
	
	if(!state) GPIOC->ODR |= GPIO_ODR_13;
		else GPIOC->ODR &= ~GPIO_ODR_13;
	
}

void EXTI0_1_IRQHandler(void)
{
		
	if((EXTI->PR & EXTI_PR_PIF0) != RESET)
	{
		if((GPIOB->IDR & GPIO_IDR_0) == SET)
		{	
			NVIC_SystemReset();
		}
	}
		
	EXTI->PR |= EXTI_PR_PIF0;
}
