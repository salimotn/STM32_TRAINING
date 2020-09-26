/**
 *************************************************************************************************
 *
 * @file      : bsp_timer.c
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
#include "bsp_timer.h"

#define BSP_TIMER_ENABLED
#ifdef BSP_TIMER_ENABLED

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
TIM_HandleTypeDef htim2;

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
void bsp_timer_init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8000;       // Clock frequecy en Mhz * 100
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = (10000 - 1);  // Period 1s =  (10000 - 1)
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim2);
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);
}

void bsp_timer_start(void)
{
  HAL_TIM_Base_Start_IT(&htim2);
}
/**
  * @}
  */

#endif /* BSP_TIMER_ENABLED */

/**
  * @}
  */
