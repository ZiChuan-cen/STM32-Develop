#include "IC.h"



void IC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    
    /* ����GPIOA��TIM2ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    /* ����GPIO */
    //PA1 -- TIM2-CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;             //��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
    /* ����ʱ�� */
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                //����Ƶ
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;         //���ϼ���
    TIM_InitStructure.TIM_Period = 65536 - 1;                         //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_InitStructure.TIM_Prescaler = 72 - 1;                      //����������Ϊ TIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_InitStructure);         //��ʼ��
	
	
	TIM_ICInitTypeDef	TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;			//�˲���
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//����ͨ��ѡ��
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM2, ENABLE);
	
}


uint32_t IC_GetFreq(void)
{
	return 1000000 / TIM_GetCapture2(TIM2);
}


