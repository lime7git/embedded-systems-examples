#include "clock.h"
#include "i2c.h"
#include "gpio.h"

volatile static uint8_t counter = 0;

int main(void)
{
	SystemInit();
	SysTick_Config(8000000/1000);
	
	GPIO_INIT();
	
	LED_SWITCH(LED_OFF);
		I2C_INIT();
		MCP23017_SET_PORTB_OUTPUTS();
	LED_SWITCH(LED_ON);
	
	while(1)
	{
		while(counter < 5)
		{
			for(uint8_t i = 0; i < 7; i++)
			{
				MCP23017_SET_PORTB_PIN_LOW_AND_OTHER_HIGH(i);
				delay_ms(20);
			}
			
			for(uint8_t j = 7; j > 0; j--)
			{
				MCP23017_SET_PORTB_PIN_LOW_AND_OTHER_HIGH(j);
				delay_ms(20);
			}
			
			counter++;
		}	
		
		MCP23017_SEND_PORTB_REGISTER(0xFF);
		
		while(counter < 10)
		{
			
			MCP23017_SEND_PORTB_REGISTER(0xC3);
			delay_ms(100);
			MCP23017_SEND_PORTB_REGISTER(0x18);
			delay_ms(150);
			MCP23017_SEND_PORTB_REGISTER(0x24);
			delay_ms(100);
			
			counter++;
		}	
		
		MCP23017_SEND_PORTB_REGISTER(0xFF);
		
		while(counter < 13)
		{
			
			MCP23017_SEND_PORTB_REGISTER(0xFF);
			delay_ms(250);
			MCP23017_SEND_PORTB_REGISTER(0x0);
			delay_ms(250);
			
			counter++;
		}	
		
		MCP23017_SEND_PORTB_REGISTER(0xFF);
		delay_ms(500);
		counter = 0;
		
	}
}
