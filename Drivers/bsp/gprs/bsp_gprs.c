/**
 *************************************************************************************************
 *
 * @file      : bsp_gprs.c
 * @date      : September 2020
 * @brief     : gprs hardware driver source code
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

/** @addtogroup gprs
  * @{
  */

/*-----------------------------------------------------------------------------------------------*/
/* Includes                                                                                      */
/*-----------------------------------------------------------------------------------------------*/
#include "bsp_gprs.h"
#include "bsp_uart.h"
#include <string.h>

#define BSP_GPRS_ENABLED
#ifdef BSP_GPRS_ENABLED

/*-----------------------------------------------------------------------------------------------*/
/* Defines                                                                                       */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup gprs_private_defines Private defines
  * @{
  */
#define BSP_GPRS_ENABLE_ATCMD_LEN               (sizeof(tstEnableAtCmds) / sizeof(bps_gprs_atcmd_t))
#define BSP_GPRS_CMD_DELAY                      (1000)
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private types                                                                                 */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup gprs_private_types Private types
  * @{
  */
typedef struct
{
  const char *pcAtCmdName;
  uint32_t u32CmdTimeoutMs;
}bps_gprs_atcmd_t;
/**
  * @}
  */
/*-----------------------------------------------------------------------------------------------*/
/* Private variables                                                                             */
/*-----------------------------------------------------------------------------------------------*/

/** @defgroup gprs_private_variables Private variables
  * @{
  */
static const bps_gprs_atcmd_t tstEnableAtCmds[] =
{
  {"AT1", BSP_GPRS_CMD_DELAY},
  {"AT2", BSP_GPRS_CMD_DELAY},
  {"AT3", BSP_GPRS_CMD_DELAY},
  {"AT4", BSP_GPRS_CMD_DELAY},
  {"AT5", BSP_GPRS_CMD_DELAY},
  {"AT6", BSP_GPRS_CMD_DELAY},
  {"AT7", BSP_GPRS_CMD_DELAY},
  {"AT8", BSP_GPRS_CMD_DELAY},
  {"AT8", BSP_GPRS_CMD_DELAY},
};
/**
  * @}
  */

/*-----------------------------------------------------------------------------------------------*/
/* Private functions                                                                             */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup gprs_private_functions Private functions
  * @{
  */

/** ***********************************************************************************************
  * @brief      Send AT command
  * @param      pAtCmd pointer to at command as defined in ::bps_gprs_atcmd_t
  * @date       July 2020
  * @return     returns nothing
  ********************************************************************************************** */
void _bsp_gprs_send_atcmd(const char * pAtCmd, uint32_t u32TimeoutMs)
{
  uint16_t u16CmdLen;

  if(pAtCmd)
  {
    u16CmdLen = strlen(pAtCmd);
    bsp_uart_transmit((uint8_t*)pAtCmd, u16CmdLen);
    HAL_Delay(u32TimeoutMs);
  }
}
/**
  * @}
  */

/*----------------------------------------------------------------------------------------------*/
/* Exported functions                                                                            */
/*-----------------------------------------------------------------------------------------------*/
/** @defgroup gprs_exported_functions Exported functions
  * @{
  */
void bsp_gprs_init(void)
{
  /* Initialization of serial interface */
  /* => already checked */
}

void bsp_gprs_enable(void)
{
  bps_gprs_atcmd_t *pAtCmd;

  pAtCmd = (bps_gprs_atcmd_t*)tstEnableAtCmds;
  for(uint8_t u08Indx=0; u08Indx < BSP_GPRS_ENABLE_ATCMD_LEN; u08Indx++)
  {
    _bsp_gprs_send_atcmd(pAtCmd->pcAtCmdName, pAtCmd->u32CmdTimeoutMs);
    pAtCmd++;
  }
}

void bsp_gprs_exit(void)
{
}
/**
  * @}
  */

#endif /* BSP_GPRS_ENABLED */

/**
  * @}
  */
