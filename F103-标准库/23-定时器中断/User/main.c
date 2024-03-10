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
#include "timer.h"


uint16_t Num = 0;

int main(void)
{
	OLED_Init();
	Timer_Init();
	display_GB2312_string(0, 1, "计数值:");
	
    while (1)
    {		
		Display_Byte(0, 9, Num/100%10);
		Display_Byte(0, 10, Num/10%10);
		Display_Byte(0, 11, Num%10);
		
		Display_Byte(1, 9, TIM_GetCounter(TIM2)/10000%10);
		Display_Byte(1, 10, TIM_GetCounter(TIM2)/1000%10);
		Display_Byte(1, 11, TIM_GetCounter(TIM2)/100%10);
		Display_Byte(1, 12, TIM_GetCounter(TIM2)/10%10);
		Display_Byte(1, 13, TIM_GetCounter(TIM2)%10);

    }
}

