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
		Display_Byte(0, 8, bmp180.Temp/1000);
        display_GB2312_string(1, 0, "气压：");
		Display_Byte(1, 8, bmp180.p/1000);
		//printf("\r\nPress:%ld\r\n",bmp180.p);

    }
}

