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
  * 平台:STM32 F103 C8T6
  *
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"
#include "PWM.h"
#include "IC.h"
#include "oled.h"



uint32_t Freq;


int main(void)
{
    OLED_Init();
    PWM_Init();
    IC_Init();

    TIM_SetCompare3(TIM3, 1000);
    while (1)
    {
        Freq = IC_GetFreq();
        display_GB2312_string(0, 1, "捕获频率：");
        Display_Byte(0, 10, Freq / 100000 % 10);
        Display_Byte(0, 11, Freq / 1000 % 10);
        Display_Byte(0, 12, Freq / 100 % 10);
        Display_Byte(0, 13, Freq / 10 % 10);
        Display_Byte(0, 14, IC_GetFreq() % 10);
        Delay_s(2);

    }
}

