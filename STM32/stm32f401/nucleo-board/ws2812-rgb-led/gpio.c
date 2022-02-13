#include "gpio.h"

void GPIO_INIT(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	// taktowanie portu A
	
	GPIOA->MODER &= ~GPIO_MODER_MODER5;	// ustawienie pinu 5 jako cyfrowe wyjscie 
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
}
	
void LED_SWITCH(eGPIO_STATE state)
{
	
	if(state) GPIOA->ODR |= GPIO_ODR_OD5;
		else GPIOA->ODR &= ~GPIO_ODR_OD5;
	
}
