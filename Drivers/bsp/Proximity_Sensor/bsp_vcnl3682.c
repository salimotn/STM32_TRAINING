/**
 *************************************************************************************************
 *
 * @file      : bsp_vcnl3682.c
 * @date      : September 2020
 * @brief     : vcnl3682 hardware driver source code
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

/** @addtogroup vcnl3682
  * @{
  */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "bsp_vcnl3682.h"
#include "bsp_i2c.h"

#define BSP_VCNL3682
#ifdef BSP_VCNL3682
/*-----------------------------------------------------------------------------------------------*/
/* Defines                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup vcnl3682 Private defines
  * @{
  */
#define VCNL3682_SLAVE_ADDR   0x60  /**<  7-bit addressing                                     */
#define PS_CONF1_CMD          0x00  /**< Standby and on / off                                  */
#define PS_CONF2_CMD          0x03  /**< PS period, persistence, interrupt and PS start / stop */
#define PS_CONF3_CMD          0x04  /**< PS mode and  LED current                              */
#define PS_THDL_CMD           0x05  /**< PS low interrupt threshold setting                    */
#define PS_THDH_CMD           0x06  /**< PS high interrupt threshold setting                   */
#define PS_CANC_CMD           0x07  /**< PS cancellation LSB setting                           */
#define PS_AC_CMD             0x08  /**<     */
#define PS_DATA_CMD           0xF8  /**<     */
#define INT_FLAG_CMD          0xF9  /**<     */
#define DEVICE_ID_CMD         0xFA  /**<     */
#define PS_AC_DATA_CMD        0xFB  /**<     */
#define DEVICE_ID_VALUE       0x26

/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private types                                                                                 */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup vcnl3682 Private types
  * @{
  */

/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private variables                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup vcnl3682 Private variables
  * @{
  */

/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private functions                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup vcnl3682 Private functions
  * @{
  */
static void _bsp_vcnl3682_write_reg(uint8_t u08Cmd ,uint16_t u16RegData)
{
  uint8_t u08CmdData[3];

  u08CmdData[0] = u08Cmd;
  u08CmdData[1] = u16RegData & 0xFF;
  u08CmdData[2] = (u16RegData >> 8) & 0xFF;
  bsp_i2c_write(VCNL3682_SLAVE_ADDR, u08CmdData, sizeof(u08CmdData));
}

static uint16_t _bsp_vcnl3682_read_reg(uint8_t u08Cmd)
{
  uint8_t u08ReadData[2];

  bsp_i2c_write(VCNL3682_SLAVE_ADDR, &u08Cmd, 1);
  bsp_i2c_read(VCNL3682_SLAVE_ADDR, u08ReadData, sizeof(u08ReadData));
  return (u08ReadData[0] | (u08ReadData[1] << 8));
}


/**
  * @}
  */

/*----------------------------------------------------------------------------------------------*/
/* Exported functions                                                                            */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup vcnl3682 Exported functions
  * @{
  */

/** ***********************************************************************************************
  * @brief      vcnl3682 initialization
  * @date       July 2020
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_vcnl3682_init(void)
{
}

/** ***********************************************************************************************
  * @brief      vcnl3682 initialization
  * @date       July 2020
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_vcnl3682_exit(void)
{
}

/** ***********************************************************************************************
  * @brief      vcnl3682 check device id
  * @date       July 2020
  * @return     Return nothing
  ********************************************************************************************** */
uint8_t bsp_vcnl3682_check_id(void)
{
  return (DEVICE_ID_VALUE == _bsp_vcnl3682_read_reg(DEVICE_ID_CMD))?1:0;
}
/**
  * @}
  */

#endif /* BSP_vcnl3682 */

/**
  * @}
  */
