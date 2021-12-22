#include "gpio.h"

void GPIO_INIT(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;	// taktowanie portu C
	
	GPIOC->MODER &= ~GPIO_MODER_MODER13;	// ustawienie pinu 13 jako cyfrowe wyjscie 
	GPIOC->MODER |= GPIO_MODER_MODER13_0;
}
	
void LED_SWITCH(eGPIO_STATE state)
{
	
	if(!state) GPIOC->ODR |= GPIO_ODR_13;
		else GPIOC->ODR &= ~GPIO_ODR_13;
	
}
