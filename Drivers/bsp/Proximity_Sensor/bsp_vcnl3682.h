/**
 *************************************************************************************************
 *
 * @file      : bsp_vcnl3682.h
 * @date      : September 2020
 * @brief     : vcnl3682 driver header file
 * @board     : {STM32l476RG}
 * @compiler  : {CubeIDE}
 * @attention
 *
 *  <h2><center>&copy; Copyright (c) 2020.
 *  All rights reserved.</center></h2>
 *
 **************************************************************************************************
 */

/** @defgroup vcnl3682 vcnl3682
  * @brief vcnl3682 driver.
  * @ingroup bsp
  * @{
  */

#ifndef _BSP_VCNL3682_H_
#define _BSP_VCNL3682_H_

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/*-----------------------------------------------------------------------------------------------*/
/* Exported defines                                                                              */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup vcnl3682_exported_defines Exported defines
  * @{
  */

 /**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Exported types                                                                                */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup vcnl3682 exported_types Exported types
  * @{
  */
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Macros                                                                                        */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup vcnl3682_exported_macros Exported macros
  * @{
  *
  */
/**
 * @}
 */
/*-----------------------------------------------------------------------------------------------*/
/* Functions                                                                                     */
/*-----------------------------------------------------------------------------------------------*/
void bsp_vcnl3682_init(void);
void bsp_vcnl3682_exit(void);
uint8_t bsp_vcnl3682_check_id(void);
void bsp_vcnl3682_set_default_cfg(void);
void bsp_vcnl3682_read(uint16_t *pu16Val);
#endif /* _BSP_VCNL3682_H_ */
/**
  * @}
  */
