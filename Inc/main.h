/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

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
#define LCD_RESET_Pin GPIO_PIN_4
#define LCD_RESET_GPIO_Port GPIOA
#define LCD_SCK_Pin GPIO_PIN_5
#define LCD_SCK_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_6
#define LCD_CS_GPIO_Port GPIOA
#define LCD_MOSI_Pin GPIO_PIN_7
#define LCD_MOSI_GPIO_Port GPIOA
#define LCD_CD_Pin GPIO_PIN_4
#define LCD_CD_GPIO_Port GPIOC
#define LCD_LED_Pin GPIO_PIN_5
#define LCD_LED_GPIO_Port GPIOC
#define SIGNAL_IN_Pin GPIO_PIN_12
#define SIGNAL_IN_GPIO_Port GPIOB
#define SIGNAL_IN_EXTI_IRQn EXTI15_10_IRQn
#define DC_IN_Pin GPIO_PIN_13
#define DC_IN_GPIO_Port GPIOB
#define DC_IN_EXTI_IRQn EXTI15_10_IRQn
#define L_OUT_Pin GPIO_PIN_14
#define L_OUT_GPIO_Port GPIOB
#define R_OUT_Pin GPIO_PIN_15
#define R_OUT_GPIO_Port GPIOB
#define T_OUT_Pin GPIO_PIN_8
#define T_OUT_GPIO_Port GPIOD
#define B_PWR_Pin GPIO_PIN_9
#define B_PWR_GPIO_Port GPIOD
#define B_ENTER_Pin GPIO_PIN_10
#define B_ENTER_GPIO_Port GPIOD
#define B_DOWN_Pin GPIO_PIN_11
#define B_DOWN_GPIO_Port GPIOD
#define B_UP_Pin GPIO_PIN_12
#define B_UP_GPIO_Port GPIOD
#define B_ESC_Pin GPIO_PIN_13
#define B_ESC_GPIO_Port GPIOD
#define FUSE_R_Pin GPIO_PIN_11
#define FUSE_R_GPIO_Port GPIOA
#define FUSE_L_Pin GPIO_PIN_12
#define FUSE_L_GPIO_Port GPIOA
#define TEMP_SCL_Pin GPIO_PIN_6
#define TEMP_SCL_GPIO_Port GPIOB
#define TEMP_SDA_Pin GPIO_PIN_7
#define TEMP_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
