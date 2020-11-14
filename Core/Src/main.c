/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "bsp_led.h"
#include "bsp_button.h"
#include "bsp_timer.h"
#include "bsp_uart.h"
#include "bsp_gprs.h"
#include "bsp_i2c.h"
#include <stdio.h>
#include "bsp_vcnl3682.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  uint8_t u08Hv;
  uint8_t u08Fv;
  uint8_t u08DutyCycle;
  uint8_t u08PayloadType;
  uint8_t u08ErrFlag;
  uint8_t u08MsgType;
  uint16_t u16MsgBuffer;
}mw_data_t;

/* Private define ------------------------------------------------------------*/
#define APP_URL         "http://iot.pestpulse.com/api/device_messages"
#define APP_DATA        "04011803030003FF,DEV_SALEM_TEST"
#define APP_DATA_SIZE   sizeof(APP_DATA)-1
#define DEVICE          "DEV_SALEM_TEST"
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint32_t u32Counter;
mw_data_t stMyData;
uint8_t t08ucmd[40];
uint8_t CmdLen;
uint8_t result;
uint16_t u16Measurement;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void mw_data_format(mw_data_t *pstData,
                    uint8_t *pu08DeviceName,
                    uint8_t *pu08Dest,
                    uint8_t *pu08CmdLen);
/* Private user code ---------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize button */
  bsp_button_init();
  /* Initialize leds */
  bsp_leds_init();
  /* Initialize timer */
  bsp_timer_init();
  /* Initialize Uart */
  bsp_uart_init();
  /* Start timer */
  bsp_timer_start();
  /* Init Ic2 driver */
  bsp_i2c_init();
  /* Check proximity sensor */
  result = bsp_vcnl3682_check_id();

  /* Enable Gprs */
  // bsp_gprs_enable();
  /* Connect to Url */
  // bsp_gprs_connect(APP_URL);
  /* Send data through GPRS */
  // stMyData.u08Hv          = 04;
  // stMyData.u08Fv          = 01;
  // stMyData.u08DutyCycle   = 18;
  // stMyData.u08PayloadType = 03;
  // stMyData.u08ErrFlag     = 03;
  // stMyData.u08MsgType     = 00;
  // stMyData.u16MsgBuffer   = 0x03FF;
  // mw_data_format(&stMyData, (uint8_t*)DEVICE, t08ucmd, &CmdLen);
  // bsp_gprs_send(t08ucmd, CmdLen);
  /* Infinite loop */
  while (1)
  {
    bsp_vcnl3682_read(&u16Measurement);
    HAL_Delay(1000);
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_USB;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 24;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
  /** Configure Uart4 source clock PCLK1 */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART4;
  PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

void app_button_pressed_handler(uint16_t * pu16count)
{
  bsp_led_ctrl(BSP_LED_ID_ALL, BSP_LED_STATE_LOW);
  switch(*pu16count)
  {
  case 1:
    bsp_led_ctrl(BSP_LED_ID_1, BSP_LED_STATE_HIGH);
    break;
  case 2:
    bsp_led_ctrl(BSP_LED_ID_2, BSP_LED_STATE_HIGH);
    break;
  case 3:
    bsp_led_ctrl(BSP_LED_ID_3, BSP_LED_STATE_HIGH);
    break;
  case 4:
    bsp_led_ctrl(BSP_LED_ID_ALL, BSP_LED_STATE_HIGH);
    *pu16count = 0;
    break;
  default:
    break;
  }
}

/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  static uint16_t u16ButtonCounter;

  if(GPIO_Pin == BSP_BUTTON_PIN)
  {
    /* Button pressed */
    u16ButtonCounter++;
    app_button_pressed_handler(&u16ButtonCounter);
  }
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  u32Counter++;
  bsp_led_toggle(BSP_LED_ID_1);
}

void mw_data_format(mw_data_t *pstData,
                    uint8_t *pu08DeviceName,
                    uint8_t *pu08Dest,
                    uint8_t *pu08CmdLen)
{
  uint8_t u08Len;
  if(pstData && pu08DeviceName && pu08Dest && pu08CmdLen)
  {
    u08Len = snprintf((char*)pu08Dest,
                      40,
                      "%02d%02d%02d%02d%02d%02d%02X%02X,%s",
                      pstData->u08Hv,
                      pstData->u08Fv,
                      pstData->u08DutyCycle,
                      pstData->u08PayloadType,
                      pstData->u08ErrFlag,
                      pstData->u08MsgType,
                      ((pstData->u16MsgBuffer >> 8)& 0xFF), /* Extract MSB */
                      (pstData->u16MsgBuffer & 0xFF),       /* Extract LSB */
                      pu08DeviceName);
    *pu08CmdLen = u08Len;
  }
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
