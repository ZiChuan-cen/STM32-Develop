#ifndef __DS18B20_H__
#define __DS18B20_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f10x.h"

/***********************   DS18B20 连接引脚定义  **************************/
#define DS18B20_Dout_GPIO_CLK_ENABLE()              RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define DS18B20_Dout_PORT                           GPIOB
#define DS18B20_Dout_PIN                            GPIO_Pin_3

/***********************   DS18B20 函数宏定义  ****************************/
#define DS18B20_Dout_LOW()                          HAL_GPIO_WritePin(DS18B20_Dout_PORT,DS18B20_Dout_PIN,GPIO_PIN_RESET)
#define DS18B20_Dout_HIGH()                         HAL_GPIO_WritePin(DS18B20_Dout_PORT,DS18B20_Dout_PIN,GPIO_PIN_SET)
#define DS18B20_Data_IN()                           HAL_GPIO_ReadPin(DS18B20_Dout_PORT,DS18B20_Dout_PIN)



#endif /* __DS18B20_H__ */


