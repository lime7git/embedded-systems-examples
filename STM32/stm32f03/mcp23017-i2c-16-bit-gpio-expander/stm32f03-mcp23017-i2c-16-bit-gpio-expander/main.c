#include "clock.h"
#include "i2c.h"
#include "gpio.h"
#include <math.h>

volatile static uint16_t cnt = 1, cnt2 = 0;
volatile static uint8_t pin = 0, state = 0;

int main(void)
{
	SystemInit();
	SysTick_Config(8000000/1000);
	
	GPIO_INIT();
	I2C_INIT();
	I2C_SET_PORTB_OUTPUTS();
	

	while(1)
	{
		if(state == 0)
		{
			if(cnt)
			{
				I2C_SEND(pin++);
				if(pin > 4) cnt = 0;
			}
			else 
			{
				I2C_SEND(pin--);
				if(pin == 0 || pin >= 250) cnt = 1;
			}
			delay_ms(15);
		}
		else if(state == 1)
		{
			I2C_SEND_REGISTER(0x2B);
			delay_ms(200);
			I2C_SEND_REGISTER(0x35);
			delay_ms(200);
			
			cnt2 += 20;
		}
		
		
		if(cnt2++ >= 100)
		{
			if(state == 1) state = 0;
			else if(state == 0) state = 1;
			
			cnt2 = 0;
		}
	}
}
