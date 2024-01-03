/**
  ******************************************************************************
  * @file    main.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-13
  * @brief   Ö÷º¯Êý
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"
#include "HC05.h"
#include "Fan.h"
#include "bsp_usart.h"


uint8_t RxSTA = 1;
int RxData[100];

int main(void)
	
{
	Usart1_Config();
	BlueTooth_Init();
	Fan_Init();

    while (1)
    {
		HC05_GetData(RxData);
		if(RxSTA == 0)
		{
			if(RxData[0] == '1')
			{
				Fan_ON();
			}
			if(RxData[0] == '0')
			{
				Fan_OFF();
			}
		}
    }
}

