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
#include "OLED.h"



int main(void)
{
    OLED_Init();

    OLED_ShowChar(1, 1, 'A');
    OLED_ShowChar(2, 2, 'B');
    OLED_ShowChar(3, 3, 'C');
    OLED_ShowChar(4, 4, 'D');
    OLED_ShowChar(3, 5, 'E');
    OLED_ShowChar(2, 6, 'F');
    OLED_ShowChar(1, 7, 'G');
    OLED_ShowChar(2, 8, 'H');
    OLED_ShowChar(3, 9, 'I');
    OLED_ShowChar(4, 10, 'J');
    OLED_ShowChar(3, 11, 'K');
    OLED_ShowChar(2, 12, 'L');
    OLED_ShowChar(1, 13, 'M');
    OLED_ShowChar(2, 14, 'N');
    OLED_ShowChar(3, 15, 'O');
    OLED_ShowChar(4, 16, 'P');
//  OLED_ShowString(2, 2, "Hello World!");


    while (1)
    {

    }
}

