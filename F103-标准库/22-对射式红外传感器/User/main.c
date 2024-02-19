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
#include "oled.h"



int main(void)
{

	OLED_Init();
	display_GB2312_string(0, 1, "Hello World!");


    while (1)
    {
		
    }
}

