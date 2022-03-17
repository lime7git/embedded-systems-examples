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
#include "adc.h"
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
#define BUTTON_VALUES_RANGES 50

#define BLACK_BUTTON_NOMINAL_VALUE 	3320
#define RED_BUTTON_NOMINAL_VALUE 		2755
#define WHITE_BUTTON_NOMINAL_VALUE 	1985
#define BLUE_BUTTON_NOMINAL_VALUE 	1248

#define SOFTWARE_CAPACITOR_RANGE 		150 

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

volatile uint16_t adc_raw;

volatile uint8_t blue_button_software_capacitor;
volatile uint8_t white_button_software_capacitor;
volatile uint8_t red_button_software_capacitor;
volatile uint8_t black_button_software_capacitor;

volatile bool buttons_locked;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
bool adc_button_range(uint16_t adc_raw_value, uint16_t BUTTON_NOMINAL_VALUE);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */
	HAL_ADC_Start(&hadc);
	
	blue_button_software_capacitor = 0;
  white_button_software_capacitor = 0;
	red_button_software_capacitor = 0;
	black_button_software_capacitor = 0;
	buttons_locked = false;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		adc_raw = HAL_ADC_GetValue(&hadc);
	
// ################################# BLUE ############################################	
		
		if(adc_button_range(adc_raw, BLUE_BUTTON_NOMINAL_VALUE))
		{
			if(blue_button_software_capacitor < 250) blue_button_software_capacitor++;
		}
		else
		{
			if(blue_button_software_capacitor > 5) blue_button_software_capacitor--;
		}

// ################################# WHITE ############################################	
		
		if(adc_button_range(adc_raw, WHITE_BUTTON_NOMINAL_VALUE))
		{
			if(white_button_software_capacitor < 250) white_button_software_capacitor++;
		}
		else
		{
			if(white_button_software_capacitor > 5) white_button_software_capacitor--;
		}

// ################################# RED ############################################	
		
		if(adc_button_range(adc_raw, RED_BUTTON_NOMINAL_VALUE))
		{
			if(red_button_software_capacitor < 250) red_button_software_capacitor++;
		}
		else
		{
			if(red_button_software_capacitor > 5) red_button_software_capacitor--;
		}
	
// ################################# BLACK ############################################	
		
		if(adc_button_range(adc_raw, BLACK_BUTTON_NOMINAL_VALUE))
		{
			if(black_button_software_capacitor < 250) black_button_software_capacitor++;
		}
		else
		{
			if(black_button_software_capacitor > 5) black_button_software_capacitor--;
		}
	
// ################################################################################################		
		
// ################################# BLUE ############################################	
		
		if(blue_button_software_capacitor > SOFTWARE_CAPACITOR_RANGE)
		{
			HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
		}

// ################################# WHITE ############################################	
		
		else if(white_button_software_capacitor > SOFTWARE_CAPACITOR_RANGE)
		{
			HAL_GPIO_WritePin(LED_WHITE_GPIO_Port, LED_WHITE_Pin, GPIO_PIN_RESET);
		}
	
// ################################# RED ############################################	
		
		else if(red_button_software_capacitor > SOFTWARE_CAPACITOR_RANGE)
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		}
// ################################# BLACK ############################################	
		
		else if(black_button_software_capacitor > SOFTWARE_CAPACITOR_RANGE)
		{
			HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_WHITE_GPIO_Port, LED_WHITE_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_WHITE_GPIO_Port, LED_WHITE_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		}
		
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
bool adc_button_range(uint16_t adc_raw_value, uint16_t BUTTON_NOMINAL_VALUE)
{
	bool ret;
	ret = false;
	
	uint16_t LOW_RANGE, HIGH_RANGE;
	
	LOW_RANGE = BUTTON_NOMINAL_VALUE - BUTTON_VALUES_RANGES;
	HIGH_RANGE = BUTTON_NOMINAL_VALUE + BUTTON_VALUES_RANGES;
	
	if( (LOW_RANGE <= adc_raw_value) && (adc_raw_value <= HIGH_RANGE) ) ret = true;
	
	return ret;
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

