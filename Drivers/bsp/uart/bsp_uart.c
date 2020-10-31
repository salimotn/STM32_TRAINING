/**
 *************************************************************************************************
 *
 * @file      : bsp_uart.c
 * @date      : September 2020
 * @brief     : uart hardware driver source code
 * @board     : {STM32l476RG Nucleo}
 * @compiler  : {IAR Embedded Workbench 8.20.1}
 *
  @verbatim
  ================================================================================================
                                 ##### How to use this driver #####
  ================================================================================================
    [..]
    The common HAL driver contains a set of generic and common APIs that can be
    used by the PPP peripheral drivers and the user to start using the HAL.
    [..]
    The HAL contains two APIs' categories:
         (+) Common HAL APIs

  @endverbatim
 **************************************************************************************************
 * @attention
 *
 *  <h2><center>&copy; Copyright (c) 2020 POC_01.
 *  All rights reserved.</center></h2>
 *
 **************************************************************************************************
 */

/** @addtogroup uart
  * @{
  */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "bsp_uart.h"
#include <string.h>

#define BSP_UART_ENABLED
#ifdef BSP_UART_ENABLED

/*-----------------------------------------------------------------------------------------------*/
/* Defines                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup uart_private_defines Private defines
  * @{
  */
#define BSP_UART_INSTANCE                        UART4
#define BSP_UART_BAUDRATE                        (115200)
#define BSP_UART_RX_SIZE                         (256)
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private types                                                                                 */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup uart_private_types Private types
  * @{
  */
uint8_t u08Indx;
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private variables                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup uart_private_variables Private variables
  * @{
  */
/* Uart instance */
UART_HandleTypeDef stUartInstance;
uint8_t u08RxByte;
uint8_t u08RxBuffer[BSP_UART_RX_SIZE];
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private functions                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup uart_private_functions Private functions
  * @{
  */

void UART4_IRQHandler(void)
{
  HAL_UART_IRQHandler(&stUartInstance);
}

/**
  * @brief Tx Transfer completed callback.
  * @param huart UART handle.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == BSP_UART_INSTANCE)
  {
  }
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == BSP_UART_INSTANCE)
  {
    u08RxBuffer[u08Indx++] = u08RxByte;
    if(u08Indx >= BSP_UART_RX_SIZE)
    {
      u08Indx = 0;
    }
    HAL_UART_Receive_IT(&stUartInstance, &u08RxByte, 1);
  }
}
/**
  * @}
  */

/*----------------------------------------------------------------------------------------------*/
/* Exported functions                                                                            */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup uart_exported_functions Exported functions
  * @{
  */

/** ***********************************************************************************************
  * @brief     uart initialization
  * @date       July 2020
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_uart_init(void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  stUartInstance.Instance = BSP_UART_INSTANCE;
  stUartInstance.Init.BaudRate = BSP_UART_BAUDRATE;
  stUartInstance.Init.WordLength = UART_WORDLENGTH_8B;
  stUartInstance.Init.StopBits = UART_STOPBITS_1;
  stUartInstance.Init.Parity = UART_PARITY_NONE;
  stUartInstance.Init.Mode = UART_MODE_TX_RX;
  stUartInstance.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  stUartInstance.Init.OverSampling = UART_OVERSAMPLING_16;
  stUartInstance.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  stUartInstance.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  HAL_UART_Init(&stUartInstance);
  /* Set Uart state to RX busy */
  HAL_UART_Receive_IT(&stUartInstance, &u08RxByte, 1);
}

/** ***********************************************************************************************
  * @brief     uart exit
  * @date       July 2020
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_uart_exit(void)
{
}

/** ***********************************************************************************************
  * @brief      Transmit data in uart interrupt mode
  * @date       July 2020
  * @param      pData pointer on data to send
  * @param      u16Len number of bytes to send
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_uart_transmit(uint8_t *pData, uint16_t u16Len)
{
  if(pData && u16Len)
  {
    HAL_UART_Transmit_IT(&stUartInstance, pData, u16Len );
  }
}


/** ***********************************************************************************************
  * @brief      Recieve data in uart interrupt mode
  * @date       July 2020
  * @param      pData pointer to destination buffer
  * @param      u16Len number of bytes to read
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_uart_received(uint8_t *pData, uint16_t u16Len)
{
  if(pData && u16Len)
  {
    memcpy(pData, u08RxBuffer, u16Len);
  }
}

/** ***********************************************************************************************
  * @brief      Recieve data in uart interrupt mode
  * @date       July 2020
  * @param      pData pointer to destination buffer
  * @param      u16Len number of bytes to read
  * @return     Return nothing
  ********************************************************************************************** */
uint32_t bsp_uart_reset_indexes(void)
{
  uint32_t u32temp;

  u32temp = u08Indx;
  u08Indx = 0;
  return u32temp;
}

/**
  * @}
  */

#endif /* BSP_UART_ENABLED */

/**
  * @}
  */
