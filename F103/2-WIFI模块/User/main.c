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
#include "bsp_usart.h"



int main(void)
{

    Usart1_Config();

    Usart3_Config();

    while (1)
    {
      printf("test \r\n");
      Delay_ms(2000);
    }
}

