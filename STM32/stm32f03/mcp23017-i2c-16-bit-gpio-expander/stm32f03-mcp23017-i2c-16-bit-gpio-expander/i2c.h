#ifndef _I2C
#define _I2C
#include <stm32f030x8.h>
#include <stm32f0xx.h>


void I2C_INIT(void);
void I2C_SET_PORTB_OUTPUTS(void);
void I2C_SEND(uint8_t PIN_NUMBER);
void I2C_SEND_REGISTER(uint8_t REG);

#endif
