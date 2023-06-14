/**
  ******************************************************************************
  * @file    main.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-13
  * @brief   主函数
  ******************************************************************************
  * @attention
  *
  * 平台:野火  STM32 F103 C8T6
  *
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"
#include "OLED.h"



int main(void)
{
    OLED_Init();

    OLED_ShowChar(1, 1, 'A');
    OLED_ShowChar(2, 2, 'B');
    OLED_ShowChar(3, 3, 'C');
    OLED_ShowChar(4, 4, 'D');
	OLED_ShowString(1, 2, "zichuan");
	OLED_ShowNum(2, 4, 1121, 4);
	OLED_ShowHexNum(3, 6, 0x1122, 4);
	OLED_ShowSignedNum(4, 8, -99, 2);
	OLED_Clear();


    while (1)
    {

    }
}

