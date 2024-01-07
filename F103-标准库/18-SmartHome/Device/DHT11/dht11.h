#ifndef __DHT_H
#define __DHT_H	 
#include "sys.h"

/************************ DHT11 数据类型定义******************************/
typedef struct
{
		uint8_t  humi_high8bit;		//原始数据：湿度高8位
		uint8_t  humi_low8bit;	 	//原始数据：湿度低8位
		uint8_t  temp_high8bit;	 	//原始数据：温度高8位
		uint8_t  temp_low8bit;	 	//原始数据：温度高8位
		uint8_t  check_sum;	 	    //校验和
		float    humidity;        //实际湿度
		float    temperature;     //实际温度  
} DHT11_Data_TypeDef;


/* 宏定义 -------------------------------------------------------------------*/
/***********************   DHT11 连接引脚定义  **************************/
#define DHT11_Dout_GPIO_CLK_ENABLE()              RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE)
#define DHT11_Dout_PORT                           GPIOB
#define DHT11_Dout_PIN                            GPIO_Pin_12

/***********************   DHT11 函数宏定义  ****************************/
#define DHT11_Dout_LOW()                          GPIO_ResetBits(DHT11_Dout_PORT,DHT11_Dout_PIN) 
#define DHT11_Dout_HIGH()                         GPIO_SetBits(DHT11_Dout_PORT,DHT11_Dout_PIN)
#define DHT11_Data_IN()	                          GPIO_ReadInputDataBit(DHT11_Dout_PORT,DHT11_Dout_PIN)



/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
void DHT11_Init( void );
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef * DHT11_Data);
#endif

