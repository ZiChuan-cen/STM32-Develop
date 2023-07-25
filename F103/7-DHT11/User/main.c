/**
  ******************************************************************************
  * @file    main.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-13
  * @brief   ������
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "stdio.h"
#include "delay.h"
#include "bsp_usart.h"
#include "dht11.h"


DHT11Data_TypeDef dht11_data = {0};				//�����ʪ�ȴ��������ص�ֵ

int Temperature = 0;

int hum = 0;


int main(void)
{
	Usart1_Config();


    while (1)
    {
		//������ʪ������
		Dht11_ReadData(&dht11_data);
		//DHT11ģ���⺯��
		DHT11_Check();
		Temperature = dht11_data.Tem;
		hum = dht11_data.Hum;
		printf("ʪ�ȣ�%d \r\n", dht11_data.Hum);
		printf("�¶ȣ�%d \r\n", dht11_data.Tem);	
		Delay_ms(1000); 

    }
}

