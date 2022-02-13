#ifndef _GPIO
#define _GPIO
#include <stm32f401xe.h>
#include <stm32f4xx.h>

typedef enum {LED_OFF = 0, LED_ON = 1}eGPIO_STATE;

	void GPIO_INIT(void);
	void LED_SWITCH(eGPIO_STATE state);
		
#endif
