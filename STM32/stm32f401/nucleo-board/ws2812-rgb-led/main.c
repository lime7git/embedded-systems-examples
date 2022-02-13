#include "main.h"

int main(void)
{
	CLOCK_INIT();
	GPIO_INIT();
	TIM1_DMA_INIT();
		
	WS2812_SET_LED(0, 255, 0, 0);
	WS2812_SEND();
	LED_SWITCH(LED_ON);
	while(1)
	{
		
	}
	
}
