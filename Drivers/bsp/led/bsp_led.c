/**
 *************************************************************************************************
 *
 * @file      : bsp_led.c
 * @date      : September 2020
 * @brief     : led hardware driver source code
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

/** @addtogroup led
  * @{
  */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "bsp_led.h"

#define BSP_LED_ENABLED
#ifdef BSP_LED_ENABLED

/*-----------------------------------------------------------------------------------------------*/
/* Defines                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup led_private_defines Private defines
  * @{
  */
#define BSP_LED_1                 GPIO_PIN_0
#define BSP_LED_2                 GPIO_PIN_1
#define BSP_LED_3                 GPIO_PIN_4
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private types                                                                                 */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup led_private_types Private types
  * @{
  */
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private variables                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup led_private_variables Private variables
  * @{
  */

/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private functions                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup led_private_functions Private functions
  * @{
  */
/** ***********************************************************************************************
  * @brief      Get the position of the bit set in the led_Pin
  * @param      u16Pin Specifies the port bit to be written
  * @date       July 2020
  * @return     led bit position
  ********************************************************************************************** */
/**
  * @}
  */

/*----------------------------------------------------------------------------------------------*/
/* Exported functions                                                                            */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup led_exported_functions Exported functions
  * @{
  */

/** ***********************************************************************************************
  * @brief      Leds initialization
  * @date       July 2020
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_leds_init(void)
{
  GPIO_InitTypeDef stGpioCfg = {0};

  /* GPIO Port Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, BSP_LED_1|BSP_LED_2|BSP_LED_3, GPIO_PIN_RESET);
  /*Configure GPIO pins : PA0 PA1 PA4 */
  stGpioCfg.Pin = BSP_LED_1|BSP_LED_2|BSP_LED_3;
  stGpioCfg.Mode = GPIO_MODE_OUTPUT_PP;
  stGpioCfg.Pull = GPIO_NOPULL;
  stGpioCfg.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &stGpioCfg);
}

/** ***********************************************************************************************
  * @brief      Leds initialization
  * @date       July 2020
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_led_ctrl(eLedId eId, eLedState eState)
{
  GPIO_PinState eGpioState;

  if((eId < BSP_LED_ID_MAX) && (eState < BSP_LED_STATE_MAX))
  {
    eGpioState = (eState == BSP_LED_STATE_HIGH)?GPIO_PIN_SET : GPIO_PIN_RESET;
    switch(eId)
    {
    case BSP_LED_ID_1:
      HAL_GPIO_WritePin(GPIOA, BSP_LED_1, eGpioState);
      break;
    case BSP_LED_ID_2:
      HAL_GPIO_WritePin(GPIOA, BSP_LED_2, eGpioState);
      break;
    case BSP_LED_ID_3:
      HAL_GPIO_WritePin(GPIOA, BSP_LED_3, eGpioState);
      break;
    case BSP_LED_ID_ALL:
      HAL_GPIO_WritePin(GPIOA, BSP_LED_1, eGpioState);
      HAL_GPIO_WritePin(GPIOA, BSP_LED_2, eGpioState);
      HAL_GPIO_WritePin(GPIOA, BSP_LED_3, eGpioState);
      break;
    default:
      break;
    }
  }
}
/**
  * @}
  */

#endif /* BSP_led_ENABLED */

/**
  * @}
  */
