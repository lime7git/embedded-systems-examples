/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_BLUE_Pin GPIO_PIN_13
#define LED_BLUE_GPIO_Port GPIOC
#define LED_GREEN_Pin GPIO_PIN_14
#define LED_GREEN_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_15
#define LED_RED_GPIO_Port GPIOC
#define G_7SEG_Pin GPIO_PIN_3
#define G_7SEG_GPIO_Port GPIOA
#define F_7SEG_Pin GPIO_PIN_4
#define F_7SEG_GPIO_Port GPIOA
#define E_7SEG_Pin GPIO_PIN_5
#define E_7SEG_GPIO_Port GPIOA
#define ENCODER_A_Pin GPIO_PIN_6
#define ENCODER_A_GPIO_Port GPIOA
#define ENCODER_B_Pin GPIO_PIN_7
#define ENCODER_B_GPIO_Port GPIOA
#define D_7SEG_Pin GPIO_PIN_0
#define D_7SEG_GPIO_Port GPIOB
#define C_7SEG_Pin GPIO_PIN_1
#define C_7SEG_GPIO_Port GPIOB
#define B_7SEG_Pin GPIO_PIN_2
#define B_7SEG_GPIO_Port GPIOB
#define A_7SEG_Pin GPIO_PIN_10
#define A_7SEG_GPIO_Port GPIOB
#define D3_7SEG_Pin GPIO_PIN_12
#define D3_7SEG_GPIO_Port GPIOB
#define D2_7SEG_Pin GPIO_PIN_13
#define D2_7SEG_GPIO_Port GPIOB
#define D1_7SEG_Pin GPIO_PIN_14
#define D1_7SEG_GPIO_Port GPIOB
#define WS2812B_DATA_PIN_Pin GPIO_PIN_8
#define WS2812B_DATA_PIN_GPIO_Port GPIOA
#define BUTTON_ENCODER_Pin GPIO_PIN_10
#define BUTTON_ENCODER_GPIO_Port GPIOA
#define BUTTON_RED_Pin GPIO_PIN_11
#define BUTTON_RED_GPIO_Port GPIOA
#define BUTTON_GREEN_Pin GPIO_PIN_5
#define BUTTON_GREEN_GPIO_Port GPIOB
#define BUTTON_BLUE_Pin GPIO_PIN_7
#define BUTTON_BLUE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
