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
#include "bsp_usart.h"
#include "delay.h"
#include "HCSR04.h"


float dis = 0;


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Usart1_Config();
	Hcsr_Init();
    while (1)
    {
		dis = Distance();
		printf("%10f \r\n", dis);
		Delay_ms(1000);
    }
}

