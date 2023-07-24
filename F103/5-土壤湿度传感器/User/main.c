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
#include "bsp_usart.h"
#include "soil_hum.h"

/* 全局变量 */

float raindata;




int main(void)
{
    Usart1_Config();

    Soil_Hum_Init();

    while (1)
    {
        raindata = (float)(Get_Adc_Average(5, 20)) * (3.3 / 4096);
        printf("raindata: %.2f \r\n", raindata);
        Delay_ms(1500);
    }
}

