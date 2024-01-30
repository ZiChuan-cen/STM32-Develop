#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"

/******************************* 引脚定义 *******************************/
#define DHT11_GPIO_CLK				RCC_APB2Periph_GPIOA
#define DHT11_Pin					GPIO_Pin_11
#define DHT11_IO					GPIOA

/***********************************************************************/

/******************************* 函数重定义 *******************************/
#define DHT11_HIGHT() 		GPIO_SetBits(GPIOA,GPIO_Pin_11);
#define DHT11_LOW()   		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
#define DHT11_ReadPin()		(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11))
/*************************************************************************/



typedef enum
{
    DHT11Mode_OUT = 1,
    DHT11Mode_IN  = 0,
} DHT11Mode_TypeDef;

typedef struct
{
    uint16_t Tem;
    uint16_t Hum;
} DHT11_Data_TypeDef;


u8 Dht11_ReadData(DHT11_Data_TypeDef *dht11);
u8 DHT11_Check(void);

#endif  /* __DHT11_H */
