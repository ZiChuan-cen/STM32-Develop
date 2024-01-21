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
#include "mlx90614.h"
#include "bsp_usart.h"



int main(void)
{
	MLX906_Init();
	Usart1_Config();


    while (1)
    {
		printf("temp=%0.2f\n",MLX906_Read_Temp());
		Delay_s(3);

    }
}

