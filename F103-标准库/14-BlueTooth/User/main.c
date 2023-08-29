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
#include "OLED.h"



uint8_t RxSTA = 1;
char RxData[100] = "None";


int main(void)
{
	BlueTooth_Init();
	OLED_Init();
	OLED_ShowString(1, 1, "RxData:");
	OLED_ShowString(2, 1, RxData);


    while (1)
    {
		HC05_GetData(RxData);
		if (RxSTA == 0)
		{
			OLED_Clear();
			OLED_ShowString(1, 1, "RxData:");
			OLED_ShowString(2, 1, RxData);
			RxSTA = 1;
		}

    }
}

