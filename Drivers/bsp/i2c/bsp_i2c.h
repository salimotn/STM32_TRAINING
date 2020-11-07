/**
 *************************************************************************************************
 *
 * @file      : bsp_i2c.h
 * @date      : September 2020
 * @brief     : i2c driver header file
 * @board     : {STM32l476RG}
 * @compiler  : {CubeIDE}
 * @attention
 *
 *  <h2><center>&copy; Copyright (c) 2020.
 *  All rights reserved.</center></h2>
 *
 **************************************************************************************************
 */

/** @defgroup i2c i2c
  * @brief i2c driver.
  * @ingroup bsp
  * @{
  */

#ifndef _BSP_I2C_H_
#define _BSP_I2C_H_

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
void bsp_i2c_init(void);
void bsp_i2c_exit(void);
void bsp_i2c_write(uint16_t u16DevAddr, uint8_t *pu08Data, uint16_t u16Len);
void bsp_i2c_read(uint16_t u16DevAddr, uint8_t *pu08Data, uint16_t u16Len);
void bsp_i2c_write_to_mem(uint16_t u16DevAddr,
                          uint16_t u16MemAddr,
                          uint16_t u16MemAddrSize,
                          uint8_t *pu08Data,
                          uint16_t u16Len);
void bsp_i2c_read_mem(uint16_t u16DevAddr,
                          uint16_t u16MemAddr,
                          uint16_t u16MemAddrSize,
                          uint8_t *pu08Data,
                          uint16_t u16Len);
#endif /* _BSP_i2c_H_ */
/**
  * @}
  */
