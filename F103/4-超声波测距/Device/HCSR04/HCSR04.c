#include "HCSR04.h"


void Hcsr_Init(void)
{
    //�����ṹ��
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    //PB6   Trig    �������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //PB7   Echo    ��������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);      //��ʼ���Ĵ���

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    //���ʱ�䣺(arr + 1) * (psc + 1) / 72000000            5000*72/72000000 = 500ms
    TIM_TimeBaseStructure.TIM_Period = 49999;
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //���ϼ���
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);



    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //ʹ���ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;      //
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);

}


