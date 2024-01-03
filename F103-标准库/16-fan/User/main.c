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
#include "Fan.h"



int main(void)
	
{
	
	Fan_Init();

    while (1)
    {
		Fan_ON();
		Delay_s(4);
		Fan_OFF();
		Delay_s(3);

    }
}

