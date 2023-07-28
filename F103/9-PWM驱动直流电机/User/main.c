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
#include "PWM.h"



int main(void)
{

    PWM_Init();

    while (1)
    {
        PWM_SetCompare3(0);
        PWM_SetCompare4(3600);
    }
}

