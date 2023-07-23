#include "HCSR04.h"
#include "delay.h"



int N = 0;
float distance = 0;

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
	GPIO_Init(GPIOB, &GPIO_InitStructure);      //��ʼ���Ĵ���
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

void TI2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		N += 1;
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//����жϱ�־λ
	
}


float Distance(void)
{
	int count = 0;
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);		//Ԥ������Trig����
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	Delay_us(20);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);		//����10us������
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0); 		//�ȴ��źŷ������źŷ�����������0,�źŷ�������Ϊ�ߵ�ƽ��������1
	//N=0;
	TIM2->CNT=0;		//us�����ȡ
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 1);		//�ȴ��źŽ��ܣ��źŷ��������У�����һֱ��λ1
	count=TIM2->CNT;
	//count = N;
	//v = 340m/s = 34000cm/s = 34000cm/10^6us = 0.034cm/us
	//s = v*t/2 = t * 0.034/2 = t * 0.017 = t/58
	distance = (float)count/58;		//��λ��cm
	return distance;
}





















