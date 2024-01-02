/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tcs34725.h"
#include "pic.h"
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
lv_ui guider_ui;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t t = 10;
/* USER CODE END Variables */
osThreadId LedFlashHandle;
osThreadId UsbDeviceHandle;
osThreadId LcdDisplayHandle;
osThreadId LvTickHandle;
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void LedFlashTask(void const *argument);
void UsbDeviceTask(void const *argument);
void LcdDisplayTask(void const *argument);
void LvTickTask(void const *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of LedFlash */
  osThreadDef(LedFlash, LedFlashTask, osPriorityBelowNormal, 0, 1024);
  LedFlashHandle = osThreadCreate(osThread(LedFlash), NULL);

  /* definition and creation of UsbDevice */
  osThreadDef(UsbDevice, UsbDeviceTask, osPriorityNormal, 0, 512);
  UsbDeviceHandle = osThreadCreate(osThread(UsbDevice), NULL);

  /* definition and creation of LcdDisplay */
  osThreadDef(LcdDisplay, LcdDisplayTask, osPriorityNormal, 0, 1024);
  LcdDisplayHandle = osThreadCreate(osThread(LcdDisplay), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  osThreadDef(LvTick, LvTickTask, osPriorityNormal, 0, 256);
  LvTickHandle = osThreadCreate(osThread(LvTick), NULL);
  /* USER CODE END RTOS_THREADS */
}

/* USER CODE BEGIN Header_LedFlashTask */
/**
 * @brief  Function implementing the LedFlash thread.
 * @param  argument: Not used
 * @retval None
 */
void LvTickTask(void const *argument)
{
  /* init code for USB_DEVICE */
  /* USER CODE BEGIN LedFlashTask */
  /* Infinite loop */
  for (;;)
  {
    lv_tick_inc(LVGL_TICK);
    osDelay(LVGL_TICK);
  }
  /* USER CODE END LedFlashTask */
}
/* USER CODE END Header_LedFlashTask */
void LedFlashTask(void const *argument)
{
  /* init code for USB_DEVICE */
  {
    vTaskSuspendAll();
    if (TCS34725_Init())
      t = 20;
    xTaskResumeAll();
  }
  /* USER CODE BEGIN LedFlashTask */
  /* Infinite loop */
  for (;;)
  {
    HAL_GPIO_TogglePin(LED_FLash_GPIO_Port, LED_FLash_Pin);
    TCS34725_GetRawData(&rgb);
    t += 1;
    osDelay(100);
  }
  /* USER CODE END LedFlashTask */
}

/* USER CODE BEGIN Header_UsbDeviceTask */
/**
 * @brief Function implementing the UsbDevice thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_UsbDeviceTask */
void UsbDeviceTask(void const *argument)
{
  /* USER CODE BEGIN UsbDeviceTask */
  /* Infinite loop */
  for (;;)
  {
    RS485_Service();
    osDelay(50);
  }
  /* USER CODE END UsbDeviceTask */
}

/* USER CODE BEGIN Header_LcdDisplayTask */
/**
 * @brief Function implementing the LcdDisplay thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_LcdDisplayTask */
void LcdDisplayTask(void const *argument)
{
  /* USER CODE BEGIN LcdDisplayTask */
  {
    vTaskSuspendAll();
    LCD_Init();
    lv_init();
    lv_port_disp_init();
    // lv_ex_label();
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    xTaskResumeAll();
  }
  // LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);

  /* Infinite loop */
  for (;;)
  {
    LCD_ShowString(10, 30, "RGB_R:", RED, WHITE, 16, 0);
    LCD_ShowIntNum(58, 30, rgb.r, 3, RED, WHITE, 16);
    LCD_ShowString(90, 30, "RGB_G:", RED, WHITE, 16, 0);
    LCD_ShowIntNum(138, 30, rgb.g, 3, RED, WHITE, 16);
    LCD_ShowString(10, 60, "RGB_B:", RED, WHITE, 16, 0);
    LCD_ShowIntNum(58, 60, rgb.b, 3, RED, WHITE, 16);
    LCD_ShowString(90, 60, "RGB_C:", RED, WHITE, 16, 0);
    LCD_ShowIntNum(138, 60, rgb.c, 3, RED, WHITE, 16);
    LCD_ShowString(10, 90, "Init Status:", RED, WHITE, 16, 0);
    LCD_ShowIntNum(108, 90, t, 3, RED, WHITE, 16);

    lv_table_set_cell_value_fmt(guider_ui.screen_table_1, 0, 0, "%d", rgb.r);
    lv_table_set_cell_value_fmt(guider_ui.screen_table_2, 0, 0, "%d", rgb.g);
    lv_table_set_cell_value_fmt(guider_ui.screen_table_3, 0, 0, "%d", rgb.b);

    // lv_tick_inc(LVGL_TICK);
    lv_task_handler();
    osDelay(LVGL_TICK);
  }
  /* USER CODE END LcdDisplayTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
