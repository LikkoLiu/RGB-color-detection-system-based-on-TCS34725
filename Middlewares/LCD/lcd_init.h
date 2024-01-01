#ifndef __LCD_INIT_H
#define __LCD_INIT_H

// #include "sys.h"
#include "main.h"
#include "cmsis_os.h"

#define USE_HORIZONTAL 0  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 280

#else
#define LCD_W 280
#define LCD_H 240
#endif




//-----------------LCD�˿ڶ���---------------- 

#define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET)//SCL=SCLK
#define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET)

#define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET)//SDA=MOSI
#define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET)

#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(uint8_t dat);//ģ��SPIʱ��
void LCD_WR_DATA8(uint8_t  dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t  dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




