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
  osThreadDef(LedFlash, LedFlashTask, osPriorityBelowNormal, 0, 2048);
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
  uint8_t cycle_cnt = 0;
  {
    vTaskSuspendAll();
    TCS34725_Init();
    initialize_window(&brightness_window);
    xTaskResumeAll();
  }
  /* USER CODE BEGIN LedFlashTask */
  /* Infinite loop */
  for (;;)
  {
    vTaskSuspendAll();
    switch (cycle_cnt)
    {
    case 12:
      if (adjust_gain(rgb, &brightness_window))
      {
        TCS34725_Disable();
        TCS34725_SetIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
        TCS34725_SetGain(brightness_window.gain);
        TCS34725_Enable();
      }
      // break;

    default:
      TCS34725_GetRawData(&rgb);
      break;
    }
    xTaskResumeAll();
    if (cycle_cnt == 12)
      cycle_cnt = 0;
    cycle_cnt++;
    osDelay(50);
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
    if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)){
      osDelay(100);
      if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
        HAL_GPIO_TogglePin(LED_FLash_GPIO_Port, LED_FLash_Pin);
    }     
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

  /* Infinite loop */
  for (;;)
  {
    lv_table_set_cell_value_fmt(guider_ui.screen_RGB_R_Value, 0, 0, "%3d(%d)", (rgb.r * 255 / rgb.c), rgb.r);
    lv_table_set_cell_value_fmt(guider_ui.screen_RGB_G_Value, 0, 0, "%3d(%d)", (rgb.g * 255 / rgb.c), rgb.g);
    lv_table_set_cell_value_fmt(guider_ui.screen_RGB_B_Value, 0, 0, "%3d(%d)", (rgb.b * 255 / rgb.c), rgb.b);
    lv_table_set_cell_value_fmt(guider_ui.screen_Clear_Value, 0, 0, "%d", rgb.c);
    lv_table_set_cell_value_fmt(guider_ui.screen_Gain_Value, 0, 0, "LEVEL %d", brightness_window.gain);
    lv_table_set_cell_value_fmt(guider_ui.screen_IR_Value, 0, 0, "%d / %d", rgb.IR, rgb.Lux);
    
    lv_led_set_color(guider_ui.screen_LED, lv_color_make((uint8_t)(rgb.r * 255 / rgb.c), (uint8_t)(rgb.g * 255 / rgb.c), (uint8_t)(rgb.b * 255 / rgb.c)));

    lv_bar_set_value(guider_ui.screen_bar_2, (rgb.r * 100) / rgb.c, LV_ANIM_ON);
    lv_bar_set_value(guider_ui.screen_bar_3, (rgb.g * 100) / rgb.c, LV_ANIM_ON);
    lv_bar_set_value(guider_ui.screen_bar_4, (rgb.b * 100) / rgb.c, LV_ANIM_ON);

    lv_task_handler();
    osDelay(LVGL_TICK);
  }
  /* USER CODE END LcdDisplayTask */
}


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
