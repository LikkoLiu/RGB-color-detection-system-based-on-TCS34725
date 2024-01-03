#ifndef __MODBUS_H
#define __MODBUS_H

#include "main.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "tcs34725.h"
#include "usbd_cdc_if.h"

#define REG_MAXNUM  (0x04 + 1)//寄存器总数 = 起始寄存器地址 + 1（REG_NUM < REG_MAXNUM）

void RS485_Service(void);
void Modbus_03_Solve(void);
void Modbus_06_Solve(void);
void Modbus_16_Solve(void);


#endif /* __LED_H */