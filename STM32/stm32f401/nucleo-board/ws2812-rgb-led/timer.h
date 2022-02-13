#ifndef _TIMER
#define _TIMER
#include <stm32f401xe.h>
#include <stm32f4xx.h>

#define PWM_START TIM1->CR1 |= TIM_CR1_CEN
#define PWM_STOP TIM1->CR1 &= ~TIM_CR1_CEN


#define LED_QUANTITY 2
#define FRAME_SIZE 24
#define RESET_SIZE 50

extern volatile uint8_t LED_DATA[LED_QUANTITY][3];
extern volatile uint16_t dma_buffer[(LED_QUANTITY * FRAME_SIZE) + RESET_SIZE];
extern volatile uint8_t flag;

void TIM1_DMA_INIT(void);
void DMA2_Stream1_IRQHandler(void);
void WS2812_SET_LED(uint8_t led_number, uint8_t red, uint8_t green, uint8_t blue);
void WS2812_SEND(void);


#endif
