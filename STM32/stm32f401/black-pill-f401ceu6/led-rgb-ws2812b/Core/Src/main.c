/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint16_t encoder_pulse_counter;
volatile uint16_t previous_encoder_pulse_counter;


volatile uint16_t pwmData[124];
volatile int green, red, blue;

volatile uint8_t state = 0;
volatile bool fast_flag = false;
															
extern volatile int16_t lcdvalue;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void send (uint8_t Green, uint8_t Red, uint8_t Blue)
{	
	
	for(int i = 49; i >= 0; i--)
	{
		pwmData[i] = 0;
	}
	
	uint8_t j = 7;
  for(int i = 50; i <= 57; i++)
	{
		if(Green & (1 << j)) pwmData[i] = 60;
		else pwmData[i] = 30;
		j--;
	}
	
	j = 7;
	for(int i = 58; i <= 65; i++)
	{
		if(Red & (1 << j)) pwmData[i] = 60;
		else pwmData[i] = 30;
		j--;
	}
	
	j = 7;
	for(int i = 66; i <= 73; i++)
	{
		if(Blue & (1 << j)) pwmData[i] = 60;
		else pwmData[i] = 30;
		j--;
	}
	
	for(int i = 123; i >= 74; i--)
	{
		pwmData[i] = 0;
	}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, 124);
	
}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	
	green = 0;
	red = 0;
	blue = 0;
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
			if(HAL_GPIO_ReadPin(BUTTON_ENCODER_GPIO_Port, BUTTON_ENCODER_Pin) == GPIO_PIN_RESET)
		{
			fast_flag = !fast_flag;
			HAL_Delay(250);	
		}
		
		if(HAL_GPIO_ReadPin(BUTTON_BLUE_GPIO_Port, BUTTON_BLUE_Pin) == GPIO_PIN_RESET)
		{
			state = 1;
			TIM3->CNT = blue;
			HAL_Delay(250);
		}
		
		if(HAL_GPIO_ReadPin(BUTTON_GREEN_GPIO_Port, BUTTON_GREEN_Pin) == GPIO_PIN_RESET)
		{
			state = 2;
			TIM3->CNT = green;
			HAL_Delay(250);
		}
		
		if(HAL_GPIO_ReadPin(BUTTON_RED_GPIO_Port, BUTTON_RED_Pin) == GPIO_PIN_RESET)
		{
			state = 3;
			TIM3->CNT = red;
			HAL_Delay(250);
		}
		
		lcdvalue = encoder_pulse_counter;
		
		previous_encoder_pulse_counter = encoder_pulse_counter;
		encoder_pulse_counter = TIM3->CNT;
		
		if(previous_encoder_pulse_counter != encoder_pulse_counter)
		{
			if(fast_flag) 
			{
				if(previous_encoder_pulse_counter > encoder_pulse_counter) encoder_pulse_counter -= 9;
				else encoder_pulse_counter += 9;
				
				TIM3->CNT = encoder_pulse_counter;
			}
		}

		
		if(encoder_pulse_counter > 255)
		{
			TIM3->CNT = 0;
			
			if(previous_encoder_pulse_counter == 0) TIM3->CNT = 255;
		}
		
		
		
		switch(state)
		{
			case 1:
			{
				blue = encoder_pulse_counter;
					HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
				break;
			}
			
			case 2:
			{
				green = encoder_pulse_counter;
					HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
				break;
			}
			
			case 3:
			{
				red = encoder_pulse_counter;
					HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
				break;
			}
		}
		
		send(green, red, blue);
		
		HAL_Delay(10);
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);
	
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PWM_PulseFinishedCallback could be implemented in the user file
   */
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

