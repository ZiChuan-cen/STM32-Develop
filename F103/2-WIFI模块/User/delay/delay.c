#include "delay.h"



uint32_t DHT11_Time = 0;


/* ��stm32f10x_it.c�ļ��е�void SysTick_Handler(void)����ע�͵�(135��) */
void SysTick_Handler(void)  //ϵͳ��ʱ���жϺ���
{

}



//ϵͳ��ʱ��
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

