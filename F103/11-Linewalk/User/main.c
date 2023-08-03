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
#include "bsp_usart.h"
//#include "stdio.h"
#include "Track.h"



int main(void)
{
	
	int i = 0;
	
	Track_GPIO_Init();
	
	Usart1_Config();
	
	
	while (1)
    {
		
		i = LineWalking();
		
		printf("%d \r\n",i);
		
		Delay_ms(1000);
		

    }
}

