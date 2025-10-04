/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define GPIO1_Pin GPIO_PIN_10
#define GPIO1_GPIO_Port GPIOB
#define GPIO2_Pin GPIO_PIN_11
#define GPIO2_GPIO_Port GPIOB
#define HDMI_KEY_Pin GPIO_PIN_12
#define HDMI_KEY_GPIO_Port GPIOB
#define HUB_KEY4_Pin GPIO_PIN_13
#define HUB_KEY4_GPIO_Port GPIOB
#define HUB_KEY3_Pin GPIO_PIN_14
#define HUB_KEY3_GPIO_Port GPIOB
#define HUB_KEY2_Pin GPIO_PIN_15
#define HUB_KEY2_GPIO_Port GPIOB
#define HUB_KEY1_Pin GPIO_PIN_8
#define HUB_KEY1_GPIO_Port GPIOA
#define Connect_TX_Pin GPIO_PIN_9
#define Connect_TX_GPIO_Port GPIOA
#define Connect_RX_Pin GPIO_PIN_10
#define Connect_RX_GPIO_Port GPIOA
#define HUB_SEL1_Pin GPIO_PIN_11
#define HUB_SEL1_GPIO_Port GPIOA
#define HUB_SEL0_Pin GPIO_PIN_12
#define HUB_SEL0_GPIO_Port GPIOA
#define HDMI_SEL2_Pin GPIO_PIN_3
#define HDMI_SEL2_GPIO_Port GPIOB
#define HDMI_SEL1_Pin GPIO_PIN_4
#define HDMI_SEL1_GPIO_Port GPIOB
#define HDMI_EN_Pin GPIO_PIN_5
#define HDMI_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
