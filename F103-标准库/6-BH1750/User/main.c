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
#include "bsp_usart.h"
#include "BH1750.h"


float Light;


int main(void)
{

	Usart1_Config();
	BH1750_Init();

    while (1)
    {
		Light = BH1750_Read_Value();
		printf("Light: %.3f \r\n",Light);
		Delay_ms(1000);

    }
}

