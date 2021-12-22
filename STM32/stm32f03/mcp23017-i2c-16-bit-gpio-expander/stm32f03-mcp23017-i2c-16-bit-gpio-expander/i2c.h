#ifndef _I2C
#define _I2C
#include <stm32f030x8.h>
#include <stm32f0xx.h>

#define MCP23017_ADDRESS 0x40
#define MCP23017_IODIR_ADDRESS 0x01				// I/O direction register, 0 - pin as output , 1 - pin as input
#define MCP23017_PORTB_GPIO_ADDRESS 0x13 	// PORTB gpio register, 0 - logic low, 1 - logic high 

void I2C_INIT(void);
void MCP23017_SET_PORTB_OUTPUTS(void);
void MCP23017_SET_PORTB_PIN_LOW_AND_OTHER_HIGH(uint8_t PIN_NUMBER);	// set pin low to turn on led 
void MCP23017_SEND_PORTB_REGISTER(uint8_t REG);

#endif
