#include "delay.h"



uint32_t DHT11_Time = 0;


/* 将stm32f10x_it.c文件中的void SysTick_Handler(void)函数注释掉(135行) */
void SysTick_Handler(void)  //系统定时器中断函数
{

}



//系统定时器
void SysTick_Init(uint32_t tick)
{
    SysTick_Config(tick);
}



void Delay_ms(uint32_t time)
{

    while (time--)
        Delay_us(1000);
}

void Delay_us(uint32_t time)
{
    while (time--)
        delay_1us();
}

void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

