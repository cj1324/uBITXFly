/**
  ******************************************************************************
  * @file    Templates/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern UART_HandleTypeDef UartHandle;
extern I2C_HandleTypeDef I2cHandle;

#define ULED_GPIO_PORT GPIOB
#define ULED_GPIO_PIN GPIO_PIN_1
#define ULED_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

#define UBTN_GPIO_PORT GPIOA
#define UBTN_GPIO_PIN GPIO_PIN_0
#define UBTN_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

/* Definition for USARTx clock resources */
#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF1_USART2
#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_AF                     GPIO_AF1_USART2

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler


#define I2Cx                           I2C1
#define I2Cx_CLK_ENABLE()              __HAL_RCC_I2C1_CLK_ENABLE()

#define I2Cx_FORCE_RESET()             __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()           __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                   GPIO_PIN_9
#define I2Cx_SCL_GPIO_PORT              GPIOA
#define I2Cx_SCL_AF                     GPIO_AF4_I2C1
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define I2Cx_SDA_PIN                    GPIO_PIN_10
#define I2Cx_SDA_GPIO_PORT              GPIOA
#define I2Cx_SDA_AF                     GPIO_AF4_I2C1
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define I2Cx_IRQn                      I2C1_IRQn
#define I2Cx_IRQHandler                I2C1_IRQHandler

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
