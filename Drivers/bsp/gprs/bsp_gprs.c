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
#include <stdio.h>

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
#define BSP_GPRS_URL_MAX                        (100)
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
  /* Start AT SYNC: Send AT every 500ms, if receive OK (Handshaking) */
  {"AT\r"                            , BSP_GPRS_CMD_DELAY},
  /* Set Echo mode off */
  {"ATE0\r"                          , BSP_GPRS_CMD_DELAY},
  /* Select a Context as Foreground Context,Expected to have id=0,channel=0 */
  {"AT+QIFGCNT=0\r"                  , BSP_GPRS_CMD_DELAY},
  /* Configure Domain Name Server */
  {"AT+QIDNSCFG?\r"                  , BSP_GPRS_CMD_DELAY},
  /* Select CSD or GPRS as the Bearer ( APN )*/
  {"AT+QICSGP=1,\"PESTPULSE.LPWA\"\r", BSP_GPRS_CMD_DELAY},
  /* Start TCP/IP stack */
  {"AT+QIREGAPP=\"PESTPULSE.LPWA\"\r", BSP_GPRS_CMD_DELAY},
  /* Disactivate PDP context */
  {"AT+QIDEACT\n"                    , BSP_GPRS_CMD_DELAY},
  /* Get Network status */
  {"AT+CREG?\n"                      , BSP_GPRS_CMD_DELAY},
  /* Set all Current Parameters to User Defined Profile */
  {"ATZ\r"                           , BSP_GPRS_CMD_DELAY},
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
  * @param      u32TimeoutMs delay counter in milliseconds
  * @date       July 2020
  * @return     returns nothing
  ********************************************************************************************** */
void _bsp_gprs_send_atcmd(const char * pAtCmd, uint32_t u32TimeoutMs)
{
  uint16_t u16CmdLen;
  // uint16_t u16ReplyLen;

  if(pAtCmd)
  {
    u16CmdLen = strlen(pAtCmd);
    bsp_uart_transmit((uint8_t*)pAtCmd, u16CmdLen);
    HAL_Delay(u32TimeoutMs);
    //  u16ReplyLen = bsp_uart_reset_indexes();
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
/** ***********************************************************************************************
  * @brief      Init modem driver
  * @date       July 2020
  * @return     returns nothing
  ********************************************************************************************** */
void bsp_gprs_init(void)
{
  /* Initialization of serial interface */
  /* => already checked */
}

/** ***********************************************************************************************
  * @brief      Enable modem driver
  * @date       July 2020
  * @return     returns nothing
  ********************************************************************************************** */
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

/** ***********************************************************************************************
  * @brief      Connect to network
  * @date       July 2020
  * @param      pcUrl URL to connect
  * @note       Input URL, you must begin with “http://” or “https://”. If the URL begins with
  *             “http://”, it indicates you willaccess a HTTP server.
  *             If the URL begins with “https://”, it indicates you will access a HTTPS server.
  * @return     returns nothing
  ********************************************************************************************** */
void bsp_gprs_connect(char *pcUrl)
{
  uint16_t u16UrlLen;
  uint8_t u08CmdLen;
  char u08AtCmd[BSP_GPRS_URL_MAX];
  // uint16_t u16ReplyLen;

  if(pcUrl)
  {
    /* 1- Format QHTTPURL command */
    u16UrlLen = strlen(pcUrl);
    u08CmdLen = snprintf(u08AtCmd, BSP_GPRS_URL_MAX, "AT+QHTTPURL=%d\r", u16UrlLen);
    /* 2- send QHTTPURL command */
    bsp_uart_transmit((uint8_t*)u08AtCmd, (uint16_t)u08CmdLen);
    HAL_Delay(BSP_GPRS_CMD_DELAY);
    // u16ReplyLen = bsp_uart_reset_indexes();
    /* 3- Send Url to connet */
    bsp_uart_transmit((uint8_t*)pcUrl, u16UrlLen);
    HAL_Delay(BSP_GPRS_CMD_DELAY);
    // u16ReplyLen = bsp_uart_reset_indexes();
  }
}

/** ***********************************************************************************************
  * @brief      Send data through modem driver
  * @date       July 2020
  * @param      pu08Data pointer to data to send
  * @param      u16DataLen data length to send
  * @return     returns nothing
  ********************************************************************************************** */
void bsp_gprs_send(uint8_t *pu08Data, uint16_t u16DataLen)
{
  uint8_t u08CmdLen;
  char u08AtCmd[BSP_GPRS_URL_MAX];
  // uint16_t u16ReplyLen;

  if(pu08Data && u16DataLen)
  {
    /* 1- Format QHTTPPOST command */
    u08CmdLen = snprintf(u08AtCmd, BSP_GPRS_URL_MAX, "AT+QHTTPPOST=%d\r", u16DataLen);
    /* 2- send QHTTPURL command */
    bsp_uart_transmit((uint8_t*)u08AtCmd, (uint16_t)u08CmdLen);
<<<<<<< HEAD
    HAL_Delay(BSP_GPRS_CMD_DELAY+4000);
    u16ReplyLen = bsp_uart_reset_indexes();
=======
    HAL_Delay(BSP_GPRS_CMD_DELAY);
    // u16ReplyLen = bsp_uart_reset_indexes();
>>>>>>> d4be9da0594b49ccc92dea8b8189bcd3965fc9b3
    /* 3- Send Url to connet */
    bsp_uart_transmit((uint8_t*)pu08Data, u16DataLen);
    HAL_Delay(BSP_GPRS_CMD_DELAY);
    // u16ReplyLen = bsp_uart_reset_indexes();
  }
}


/** ***********************************************************************************************
  * @brief      Disconnect from network
  * @date       July 2020
  * @return     returns nothing
  ********************************************************************************************** */
void bsp_gprs_disconnect(void)
{
}



/** ***********************************************************************************************
  * @brief      receive data through modem driver
  * @date       July 2020
  * @return     returns nothing
  ********************************************************************************************** */
void bsp_gprs_receive(void)
{
}

/** ***********************************************************************************************
  * @brief      Exit modem driver
  * @date       July 2020
  * @return     returns nothing
  ********************************************************************************************** */
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
