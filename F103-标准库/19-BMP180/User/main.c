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
#include "BMP180.h"
#include "oled.h"
#include "delay.h"
#include "bsp_usart.h"


int main(void)
{
	Usart1_Config();
	BMP_Init();
    OLED_Init();
	BMP_ReadCalibrationData();

    while (1)
    {
		BMP_UncompemstatedToTrue();
		
		display_GB2312_string(0, 0, "温度：");
		Display_Byte(0, 7, bmp180.Temp/100);
		Display_Byte(0, 9, bmp180.Temp/10%10);
		
        display_GB2312_string(1, 0, "气压：");
		Display_Byte(1, 7, bmp180.p/100000);
		Display_Byte(1, 9, bmp180.p/10000%10);
		Display_Byte(1, 11, bmp180.p/1000%100);
		Display_Byte(1, 13, bmp180.p/100%1000);
		
//		display_GB2312_string(2, 0, "海拔：");
//		Display_Byte(2, 7, bmp180.altitude);
//		Display_Byte(2, 9, bmp180.altitude);		
//		printf("\r\naltitudes:%ld\r\n",bmp180.altitude);
//		delay_s(2);

    }
}

