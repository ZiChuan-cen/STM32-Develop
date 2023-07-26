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
#include "OLED.h"



int main(void)
{
    OLED_Init();

    OLED_ShowChar(1, 1, 'A');
    OLED_ShowChar(2, 2, 'B');
    OLED_ShowChar(3, 3, 'C');
    OLED_ShowChar(4, 4, 'D');
	OLED_ShowString(1, 4, "zichuan");
	OLED_ShowNum(2, 4, 1121, 4);
	OLED_ShowHexNum(3, 6, 0x1122, 4);
	OLED_ShowSignedNum(4, 8, -99, 2);
    OLED_ShowChinese(1, 1, 0);
    OLED_ShowChinese(1, 2, 1);
    OLED_ShowChinese(1, 3, 2);
    OLED_ShowChinese(1, 4, 3);
    OLED_ShowChinese(1, 5, 4);
    OLED_ShowChinese(1, 6, 5);
	OLED_BMP(3);
	Delay_ms(2000);
    //OLED_Clear();

    while (1)
    {
//		for(int i=3; i<9; i++)
//		{
//			OLED_BMP(i);
//			Delay_ms(50);
//		}

    }
}

