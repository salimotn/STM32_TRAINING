/**
 *************************************************************************************************
 *
 * @file      : bsp_led.h
 * @date      : September 2020
 * @brief     : led driver header file
 * @board     : {STM32l476RG}
 * @compiler  : {CubeIDE}
 * @attention
 *
 *  <h2><center>&copy; Copyright (c) 2020.
 *  All rights reserved.</center></h2>
 *
 **************************************************************************************************
 */

/** @defgroup led LED
  * @brief LED driver.
  * @ingroup bsp
  * @{
  */

#ifndef _BSP_LED_H_
#define _BSP_LED_H_

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/*-----------------------------------------------------------------------------------------------*/
/* Exported defines                                                                              */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup exported Exported defines
  * @{
  */
// Exported defines here
 /**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Exported types                                                                                */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup exported Exported types
  * @{
  */
/** Led ID type */
typedef enum
{
  BSP_LED_ID_1  = 0,                        /**< Led 1 id         */
  BSP_LED_ID_2     ,                        /**< Led 2 id         */
  BSP_LED_ID_3     ,
  BSP_LED_ID_ALL   ,
  BSP_LED_ID_MAX   ,
}eLedId;

typedef enum
{
  BSP_LED_STATE_LOW = 0,
  BSP_LED_STATE_HIGH   ,
  /* BSP_LED_STATE_BLINK  , */            /**< Not supported yet */
  BSP_LED_STATE_MAX
}eLedState;

/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Macros                                                                                        */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup gpio_exported_macros Exported macros
  * @{
  *
  */

/**
 * @}
 */
/*-----------------------------------------------------------------------------------------------*/
/* Functions                                                                                     */
/*-----------------------------------------------------------------------------------------------*/
void bsp_leds_init(void);
void bsp_led_ctrl(eLedId eId, eLedState eState);
#endif /* _BSP_LED_H_ */

/**
  * @}
  */
