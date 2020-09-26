/**
 *************************************************************************************************
 *
 * @file      : bsp_button.c
 * @date      : September 2020
 * @brief     : button hardware driver source code
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

/** @addtogroup button
  * @{
  */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "bsp_button.h"

#define BSP_BUTTON_ENABLED
#ifdef BSP_BUTTON_ENABLED

/*-----------------------------------------------------------------------------------------------*/
/* Defines                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup button_private_defines Private defines
  * @{
  */

/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private types                                                                                 */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup button_private_types Private types
  * @{
  */
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private variables                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup button_private_variables Private variables
  * @{
  */

/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private functions                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup button_private_functions Private functions
  * @{
  */

/** ***********************************************************************************************
  * @brief      Get the position of the bit set in the button_Pin
  * @param      u16Pin Specifies the port bit to be written
  * @date       July 2020
  * @return     button bit position
  ********************************************************************************************** */
/**
  * @}
  */

/*----------------------------------------------------------------------------------------------*/
/* Exported functions                                                                            */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup button_exported_functions Exported functions
  * @{
  */
void bsp_button_init(void)
{
	GPIO_InitTypeDef stGpioCfg = {0};

	/* GPIO Port Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	/*Configure GPIO pin : PC13 */
	stGpioCfg.Pin = BSP_BUTTON_PIN;
	stGpioCfg.Mode = GPIO_MODE_IT_RISING;
	stGpioCfg.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &stGpioCfg);
  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
/**
  * @}
  */

#endif /* BSP_BUTTON_ENABLED */

/**
  * @}
  */
