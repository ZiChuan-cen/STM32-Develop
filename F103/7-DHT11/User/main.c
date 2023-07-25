/**
  ******************************************************************************
  * @file    main.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-13
  * @brief   主函数
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "stdio.h"
#include "delay.h"
#include "bsp_usart.h"
#include "dht11.h"


DHT11Data_TypeDef dht11_data = {0};				//存放温湿度传感器返回的值

int Temperature = 0;

int hum = 0;


int main(void)
{
	Usart1_Config();


    while (1)
    {
		//环境温湿度数据
		Dht11_ReadData(&dht11_data);
		//DHT11模块检测函数
		DHT11_Check();
		Temperature = dht11_data.Tem;
		hum = dht11_data.Hum;
		printf("湿度：%d \r\n", dht11_data.Hum);
		printf("温度：%d \r\n", dht11_data.Tem);	
		Delay_ms(1000); 

    }
}

