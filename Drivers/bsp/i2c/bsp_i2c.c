/**
 *************************************************************************************************
 *
 * @file      : bsp_i2c.c
 * @date      : September 2020
 * @brief     : i2c hardware driver source code
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

/** @addtogroup i2c
  * @{
  */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "bsp_i2c.h"

#define BSP_I2C_ENABLED
#ifdef BSP_I2C_ENABLED
/*-----------------------------------------------------------------------------------------------*/
/* Defines                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup i2c_private_defines Private defines
  * @{
  */
#define BSP_I2C_INSTANCE             I2C3
#define BSP_I2C_TIMEOUT              10000
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private types                                                                                 */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup i2c_private_types Private types
  * @{
  */
I2C_HandleTypeDef stI2cInstance;
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private variables                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup i2c_private_variables Private variables
  * @{
  */

/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private functions                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup i2c_private_functions Private functions
  * @{
  */

/**
  * @}
  */

/*----------------------------------------------------------------------------------------------*/
/* Exported functions                                                                            */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup i2c_exported_functions Exported functions
  * @{
  */

/** ***********************************************************************************************
  * @brief      i2cs initialization
  * @date       July 2020
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_i2c_init(void)
{
  stI2cInstance.Instance = BSP_I2C_INSTANCE;
  stI2cInstance.Init.Timing = 0x00505B89;
  stI2cInstance.Init.OwnAddress1 = 0;
  stI2cInstance.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  stI2cInstance.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  stI2cInstance.Init.OwnAddress2 = 0;
  stI2cInstance.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  stI2cInstance.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  stI2cInstance.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&stI2cInstance);
  /** Configure Analogue filter */
  HAL_I2CEx_ConfigAnalogFilter(&stI2cInstance, I2C_ANALOGFILTER_ENABLE);
  /** Configure Digital filter */
  HAL_I2CEx_ConfigDigitalFilter(&stI2cInstance, 0);
}

/** ***********************************************************************************************
  * @brief      i2cs initialization
  * @date       July 2020
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_i2c_exit(void)
{
}


/** ***********************************************************************************************
  * @brief      Transmit an amount of data in non-blocking mode with Interrupt
  * @date       July 2020
  * @param      u16DevAddr Target device address: The device 7 bits address value
  *             in datasheet must be shifted to the left before calling the interface
  * @param      pu08Data Pointer to data buffer
  * @param      u16Len Amount of data to be sent
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_i2c_write(uint16_t u16DevAddr, uint8_t *pu08Data, uint16_t u16Len)
{
  if(pu08Data && u16Len)
  {
    HAL_I2C_Master_Transmit(&stI2cInstance, u16DevAddr, pu08Data, u16Len, BSP_I2C_TIMEOUT);
  }
}

/** ***********************************************************************************************
  * @brief      i2cs initialization
  * @date       July 2020
  * @param      u16DevAddr Target device address: The device 7 bits address value
  *             in datasheet must be shifted to the left before calling the interface
  * @param      pu08Data Pointer to data buffer to receive in
  * @param      u16Len Amount of data to be receivedq
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_i2c_read(uint16_t u16DevAddr, uint8_t *pu08Data, uint16_t u16Len)
{
  if(pu08Data && u16Len)
  {
    HAL_I2C_Master_Receive(&stI2cInstance, u16DevAddr, pu08Data, u16Len, BSP_I2C_TIMEOUT);
  }
}

/** ***********************************************************************************************
  * @brief      i2cs initialization
  * @date       July 2020
  * @param      u16DevAddr Target device address: The device 7 bits address value
  *             in datasheet must be shifted to the left before calling the interface
  * @param      pu08Data Pointer to data buffer to receive in
  * @param      u16Len Amount of data to be received
  * @return     Return nothing
  ********************************************************************************************** */
  void bsp_i2c_write_to_mem(uint16_t u16DevAddr,
                            uint16_t u16MemAddr,
                            uint16_t u16MemAddrSize,
                            uint8_t *pu08Data,
                            uint16_t u16Len)
{
  if(u16MemAddrSize && pu08Data && u16Len)
  {
    HAL_I2C_Mem_Write(&stI2cInstance,
                      u16DevAddr,
                      u16MemAddr,
                      u16MemAddrSize,
                      pu08Data,
                      u16Len,
                      BSP_I2C_TIMEOUT);
  }
}



/** ***********************************************************************************************
  * @brief      i2cs initialization
  * @date       July 2020
  * @param      u16DevAddr Target device address: The device 7 bits address value
  *             in datasheet must be shifted to the left before calling the interface
  * @param      pu08Data Pointer to data buffer to receive in
  * @param      u16Len Amount of data to be receivedq
  * @return     Return nothing
  ********************************************************************************************** */
void bsp_i2c_read_mem(uint16_t u16DevAddr,
                          uint16_t u16MemAddr,
                          uint16_t u16MemAddrSize,
                          uint8_t *pu08Data,
                          uint16_t u16Len)
{
  if(u16MemAddrSize && pu08Data && u16Len)
  {
    HAL_I2C_Mem_Read(&stI2cInstance,
                     u16DevAddr,
                     u16MemAddr,
                     u16MemAddrSize,
                     pu08Data,
                     u16Len,
                     BSP_I2C_TIMEOUT);
  }
}
/**
  * @}
  */
#endif /* BSP_I2C_ENABLED */

/**
  * @}
  */
