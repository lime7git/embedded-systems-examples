#include "timer.h"

volatile uint8_t LED_DATA[LED_QUANTITY][3];
volatile uint16_t dma_buffer[(LED_QUANTITY * FRAME_SIZE) + RESET_SIZE];
volatile uint8_t flag = 0;

void TIM1_DMA_INIT(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	
	// set PB1 as alternative function TIM3_CH4, pull-down
	GPIOA->MODER &= ~GPIO_MODER_MODER8;
	GPIOA->MODER |= GPIO_MODER_MODER8_1;
	GPIOA->AFR[1] |= 0x00000001;
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	// ~800khz frequency
	TIM1->PSC = 1 - 1;	// 
	TIM1->ARR = 100 - 1;
	
	//set tim as pwm, enable channel and timer
	TIM1->CCER |= TIM_CCER_CC1E;
	TIM1->CCMR1 |= (7 << TIM_CCMR1_OC1M_Pos);
	TIM1->BDTR |= TIM_BDTR_MOE;
	TIM1->DIER |= TIM_DIER_CC1DE;
	
	DMA2_Stream1->PAR = (uint32_t)&TIM1->CCR1;
	DMA2_Stream1->M0AR = (uint32_t)dma_buffer;
	//DMA2_Stream6->NDTR = (uint16_t)((LED_QUANTITY * FRAME_SIZE) + RESET_SIZE);
	DMA2_Stream1->CR &= ~DMA_SxCR_EN;
	DMA2_Stream1->CR |= (6 << DMA_SxCR_CHSEL_Pos) | (1 << DMA_SxCR_DIR_Pos) | DMA_SxCR_TCIE | (0 << DMA_SxCR_CIRC_Pos) 
											| DMA_SxCR_MINC | (1 << DMA_SxCR_PSIZE_Pos) | (1 << DMA_SxCR_MSIZE_Pos);
	NVIC_EnableIRQ(DMA2_Stream1_IRQn);
	
}

void DMA2_Stream1_IRQHandler(void)
{
	if((DMA2->LISR & DMA_LISR_TCIF1) == !RESET )
	{
		DMA2->LIFCR |= DMA_LIFCR_CTCIF1;
		
		PWM_STOP;
		flag = 1;
	}
	
}


void WS2812_SET_LED(uint8_t led_number, uint8_t red, uint8_t green, uint8_t blue)
{
	LED_DATA[led_number][0] = green;
	LED_DATA[led_number][1] = red;
	LED_DATA[led_number][2] = blue;
}

void WS2812_SEND(void)
{
	uint16_t index = 0;
	
	for(uint8_t i = 0; i < LED_QUANTITY; i++)
	{
		for(uint8_t j = 0; j < 3; j++)
		{
			for(int k = 7; k >= 0; k--)
			{
				if(LED_DATA[i][j] & (1 << k)) dma_buffer[index] = 64;
					else dma_buffer[index] = 32;
			
				index++;
			}
		}
	}
	
	for(uint8_t i = 0; i < 50; i++)
	{
		dma_buffer[index] = 0;
		index++;
	}
	
	PWM_START;
	DMA2_Stream6->CR &= ~DMA_SxCR_EN;
	DMA2_Stream6->NDTR = index;
	DMA2_Stream6->CR |= DMA_SxCR_EN;
	
	while(!flag){}
		flag = 0;
	
}
