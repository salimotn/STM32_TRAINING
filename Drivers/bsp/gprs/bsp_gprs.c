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
#define BSP_GPRS_CMD_DELAY                      (3000)
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
  {"AT\r"                            , BSP_GPRS_CMD_DELAY},
  {"ATE0\r"                          , BSP_GPRS_CMD_DELAY},
  {"AT+QIFGCNT=0\r\n"                  , BSP_GPRS_CMD_DELAY},
  {"AT+QIDNSCFG?\r\n"                  , BSP_GPRS_CMD_DELAY},
  {"AT+QICSGP=1,\"PESTPULSE.LPWA\"\r\n", BSP_GPRS_CMD_DELAY},
  {"AT+QIREGAPP=\"PESTPULSE.LPWA\"\r\n", BSP_GPRS_CMD_DELAY},
  {"AT+QIDEACT\r\n"                    , BSP_GPRS_CMD_DELAY},
  {"AT+CREG?\r\n"                      , BSP_GPRS_CMD_DELAY},
  /* Set all Current Parameters to User Defined Profile */
  {"ATZ\r\n"                           , BSP_GPRS_CMD_DELAY},
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
  uint16_t u16ReplyLen;

  if(pAtCmd)
  {
    u16CmdLen = strlen(pAtCmd);
    bsp_uart_transmit((uint8_t*)pAtCmd, u16CmdLen);
    HAL_Delay(u32TimeoutMs);
    u16ReplyLen = bsp_uart_reset_indexes();
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
