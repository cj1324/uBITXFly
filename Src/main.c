/**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @brief   Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F0xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static GPIO_InitTypeDef  GPIO_InitStruct_LED, GPIO_InitStruct_BTN;
UART_HandleTypeDef UartHandle;
I2C_HandleTypeDef  I2cHandle;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void UART_Init(void);
static void I2C_Init(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

    /* STM32F0xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Low Level Initialization
     */
    HAL_Init();

    /* Configure the system clock to have a system clock = 48 Mhz */
    SystemClock_Config();

    ULED_CLK_ENABLE();
    GPIO_InitStruct_LED.Pin = ULED_GPIO_PIN;
    GPIO_InitStruct_LED.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct_LED.Pull  = GPIO_PULLUP;
    GPIO_InitStruct_LED.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(ULED_GPIO_PORT, &GPIO_InitStruct_LED);
    HAL_GPIO_WritePin(ULED_GPIO_PORT, ULED_GPIO_PIN, GPIO_PIN_SET);

    UBTN_CLK_ENABLE();
    GPIO_InitStruct_BTN.Pin = UBTN_GPIO_PIN;
    GPIO_InitStruct_BTN.Mode  = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct_BTN.Pull  = GPIO_PULLUP;
    GPIO_InitStruct_BTN.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(UBTN_GPIO_PORT, &GPIO_InitStruct_BTN);

    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

    UART_Init();
    I2C_Init();


    HAL_GPIO_WritePin(ULED_GPIO_PORT, ULED_GPIO_PIN, GPIO_PIN_RESET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(ULED_GPIO_PORT, ULED_GPIO_PIN, GPIO_PIN_SET);


    char * debug = "Loop ";
    while (1) {
        HAL_Delay(2000);
        HAL_UART_Transmit(&UartHandle, (uint8_t *)debug, 5, 0xFFFF);
    }

    Error_Handler();
}

static void UART_Init(void){
    /*##-1- Configure the UART peripheral ######################################*/
    /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
    /* UART configured as follows:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
    UartHandle.Instance        = USARTx;
    UartHandle.Init.BaudRate   = 115200;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX;
    UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT; 
    if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
    {
        Error_Handler();
    }
    if(HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        Error_Handler();
    }

}

static void I2C_Init(void){
    I2cHandle.Instance = I2Cx;
    I2cHandle.Init.Timing = 0x00905E82;
    I2cHandle.Init.OwnAddress1     = 0x1E;
    I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2cHandle.Init.OwnAddress2     = 0x1F;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
    if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler();
    }

    /* Enable the Analog I2C Filter */
    HAL_I2CEx_ConfigAnalogFilter(&I2cHandle,I2C_ANALOGFILTER_ENABLE);
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){
    uint8_t errno = HAL_I2C_GetError(&I2cHandle);
    while (1) {
        HAL_Delay(100);
        HAL_GPIO_TogglePin(ULED_GPIO_PORT, ULED_GPIO_PIN);
    }

}
void HAL_GPIO_EXTI_Callback(uint16_t pin) {
  if (pin == UBTN_GPIO_PIN){
    HAL_GPIO_TogglePin(ULED_GPIO_PORT, ULED_GPIO_PIN);
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            HSE Frequency(Hz)              = 16000000
  *            System Clock source            = PLL (HSE / 2 * 6)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            PREDIV                         = 2
  *            PLLMUL                         = 6
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* No HSE Oscillator on Nucleo, Activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState        = RCC_HSI_ON;
  RCC_OscInitStruct.HSEState        = RCC_HSE_ON;
  RCC_OscInitStruct.HSICalibrationValue  = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PREDIV      = RCC_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
    while (1) {
        HAL_Delay(100);
        HAL_UART_Transmit(&UartHandle, (uint8_t *)'E', 1, 0xFFFF);
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
