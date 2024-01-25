#ifndef __DS18B20_H__
#define __DS18B20_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f10x.h"

/***********************   DS18B20 连接引脚定义  **************************/
#define DS18B20_Dout_GPIO_CLK_ENABLE()              RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define DS18B20_Dout_PORT                           GPIOB
#define DS18B20_Dout_PIN                            GPIO_Pin_3

/***********************   DS18B20 函数宏定义  ****************************/
#define DS18B20_Dout_LOW()						GPIO_ResetBits(DS18B20_Dout_PORT, DS18B20_Dout_PIN)
#define DS18B20_Dout_HIGH()						GPIO_SetBits(DS18B20_Dout_PORT, DS18B20_Dout_PIN)
#define DS18B20_Data_IN()						GPIO_ReadInputDataBit(DS18B20_Dout_PORT,DS18B20_Dout_PIN)



/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
unsigned char DS18B20_Init(void);//初始化DS18B20
short DS18B20_Get_Temp(void);//获取温度
void DS18B20_Start(void);//开始温度转换

void DS18B20_Write_Byte(unsigned char dat);//写入一个字节
unsigned char DS18B20_Read_Byte(void);//读出一个字节
unsigned char DS18B20_Read_Bit(void);//读出一个位
unsigned char DS18B20_Check(void);//检测是否存在DS18B20
void DS18B20_Rst(void);//复位DS18B20  



#endif /* __DS18B20_H__ */


