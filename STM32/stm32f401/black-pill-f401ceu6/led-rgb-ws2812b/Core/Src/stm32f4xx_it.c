/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#include "stdlib.h"
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
															
volatile uint8_t lcdpos = 0;
volatile int16_t lcdvalue = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

void Led7seg_WriteDigit(uint8_t pos, uint8_t num)
{
	GPIOB->ODR &= ~GPIO_ODR_OD10;	//	B
	GPIOB->ODR &= ~GPIO_ODR_OD2;	// 	F
	GPIOB->ODR &= ~GPIO_ODR_OD1;	// 	A
	GPIOB->ODR &= ~GPIO_ODR_OD0;	//	G
	GPIOA->ODR &= ~GPIO_ODR_OD5;	//	C
	GPIOA->ODR &= ~GPIO_ODR_OD4;	//	E
	GPIOA->ODR &= ~GPIO_ODR_OD3;	//	D
	
	GPIOB->ODR &= ~GPIO_ODR_OD12;	
	GPIOB->ODR &= ~GPIO_ODR_OD13;
	GPIOB->ODR &= ~GPIO_ODR_OD14;
	
	switch(pos)
	{
		case 0:	GPIOB->ODR |= GPIO_ODR_OD12;	break;
		case 1:	GPIOB->ODR |= GPIO_ODR_OD13;	break;
		case 2:	GPIOB->ODR |= GPIO_ODR_OD14;	break;
	}
	switch(num)
	{
		case 0:
			GPIOB->ODR |= GPIO_ODR_OD1; 	// A
			GPIOB->ODR |= GPIO_ODR_OD10;	// B
			GPIOA->ODR |= GPIO_ODR_OD5;		// C
			GPIOA->ODR |= GPIO_ODR_OD3;		// D
			GPIOA->ODR |= GPIO_ODR_OD4;		// E
			GPIOB->ODR |= GPIO_ODR_OD2;		// F
			break;
		case 1:
			GPIOB->ODR |= GPIO_ODR_OD10;	// B
			GPIOA->ODR |= GPIO_ODR_OD5;		// C
			break;
		case 2:
			GPIOB->ODR |= GPIO_ODR_OD1; 	// A
			GPIOB->ODR |= GPIO_ODR_OD10;	// B
			GPIOA->ODR |= GPIO_ODR_OD3;		// D
			GPIOA->ODR |= GPIO_ODR_OD4;		// E
			GPIOB->ODR |= GPIO_ODR_OD0;		// G
			break;
		case 3:
			GPIOB->ODR |= GPIO_ODR_OD1; 	// A
			GPIOB->ODR |= GPIO_ODR_OD10;	// B
			GPIOA->ODR |= GPIO_ODR_OD5;		// C
			GPIOA->ODR |= GPIO_ODR_OD3;		// D
			GPIOB->ODR |= GPIO_ODR_OD0;		// G
			break;
		case 4:
			GPIOB->ODR |= GPIO_ODR_OD10;	// B
			GPIOA->ODR |= GPIO_ODR_OD5;		// C
			GPIOB->ODR |= GPIO_ODR_OD2;		// F
			GPIOB->ODR |= GPIO_ODR_OD0;		// G
			break;
		case 5:
			GPIOB->ODR |= GPIO_ODR_OD1; 	// A
			GPIOA->ODR |= GPIO_ODR_OD5;		// C
			GPIOA->ODR |= GPIO_ODR_OD3;		// D
			GPIOB->ODR |= GPIO_ODR_OD2;		// F
			GPIOB->ODR |= GPIO_ODR_OD0;		// G
			break;
		case 6:
			GPIOB->ODR |= GPIO_ODR_OD1; 	// A
			GPIOA->ODR |= GPIO_ODR_OD5;		// C
			GPIOA->ODR |= GPIO_ODR_OD3;		// D
			GPIOA->ODR |= GPIO_ODR_OD4;		// E
			GPIOB->ODR |= GPIO_ODR_OD2;		// F
			GPIOB->ODR |= GPIO_ODR_OD0;		// G
			break;
		case 7:
			GPIOB->ODR |= GPIO_ODR_OD1; 	// A
			GPIOB->ODR |= GPIO_ODR_OD10;	// B
			GPIOA->ODR |= GPIO_ODR_OD5;		// C
			break;
		case 8:
			GPIOB->ODR |= GPIO_ODR_OD1; 	// A
			GPIOB->ODR |= GPIO_ODR_OD10;	// B
			GPIOA->ODR |= GPIO_ODR_OD5;		// C
			GPIOA->ODR |= GPIO_ODR_OD3;		// D
			GPIOA->ODR |= GPIO_ODR_OD4;		// E
			GPIOB->ODR |= GPIO_ODR_OD2;		// F
			GPIOB->ODR |= GPIO_ODR_OD0;		// G
			break;
		case 9:
			GPIOB->ODR |= GPIO_ODR_OD1; 	// A
			GPIOB->ODR |= GPIO_ODR_OD10;	// B
			GPIOA->ODR |= GPIO_ODR_OD5;		// C
			GPIOB->ODR |= GPIO_ODR_OD2;		// F
			GPIOB->ODR |= GPIO_ODR_OD0;		// G
			break;
	}
}

void Led7seg_WriteNumber(void)
{	
	uint8_t tab[3];
	
	if(lcdvalue >=0 )
	{		
		tab[1] = (lcdvalue % 10) / 1;
		tab[2] = (lcdvalue % 100) / 10;
		tab[0] = (lcdvalue % 1000) / 100;
	}
	
	Led7seg_WriteDigit(lcdpos, tab[lcdpos]);
	lcdpos++;
	if(lcdpos >= 3)
		lcdpos = 0;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_tim1_ch1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	Led7seg_WriteNumber();
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA2 stream1 global interrupt.
  */
void DMA2_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream1_IRQn 0 */

  /* USER CODE END DMA2_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim1_ch1);
  /* USER CODE BEGIN DMA2_Stream1_IRQn 1 */

  /* USER CODE END DMA2_Stream1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

