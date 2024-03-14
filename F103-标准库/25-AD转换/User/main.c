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
#include "delay.h"
#include "oled.h"
#include "AD.h"


uint16_t AD_Value;


int main(void)
{
	OLED_Init();
	AD_Init();


    while (1)
    {
		AD_Value = Get_Value();
		Display_Byte(2, 6, AD_Value/10000%10);
		Display_Byte(2, 7, AD_Value/1000%10);
		Display_Byte(2, 8, AD_Value/100%10);
		Display_Byte(2, 9, AD_Value/100%10);
		Display_Byte(2, 10, AD_Value/10%10);
		Display_Byte(2, 11, AD_Value%10);
		AD_Value = (float)AD_Value / 4095 * 3.3 * 100;
		display_GB2312_string(0, 1, "转换值：");
		Display_Byte(1, 7, AD_Value/10000%10);
		Display_Byte(1, 8, AD_Value/1000%10);
		Display_Byte(0, 8, AD_Value/100%10);
		Display_Byte(0, 9, AD_Value/100%10);
		Display_Byte(0, 10, AD_Value/10%10);
		Display_Byte(0, 11, AD_Value%10);
		Delay_s(1);

    }
	
}

