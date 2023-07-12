#include "HCSR04.h"


void Hcsr_Init(void)
{
    //创建结构体
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    //PB6   Trig    推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //PB7   Echo    下拉输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);      //初始化寄存器

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    //溢出时间：(arr + 1) * (psc + 1) / 72000000            5000*72/72000000 = 500ms
    TIM_TimeBaseStructure.TIM_Period = 49999;
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);



    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //使能中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;      //
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);

}


