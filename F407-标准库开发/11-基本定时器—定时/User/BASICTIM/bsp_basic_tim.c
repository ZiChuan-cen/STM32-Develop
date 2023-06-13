#include "bsp_basic_tim.h"

static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);    // �����ж���Ϊ0
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQn;    // �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    // ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


static void TIM_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE);    // ����TIMx_CLK,x[6,7]

    /* �ۼ� TIM_Period�������һ�����»����ж�*/
    //����ʱ����0������4999����Ϊ5000�Σ�Ϊһ����ʱ����
    TIM_TimeBaseStructure.TIM_Period = 5000 - 1;

    //��ʱ��ʱ��ԴTIMxCLK = 2 * PCLK1
    //                PCLK1 = HCLK / 4
    //                => TIMxCLK=HCLK/2=SystemCoreClock/2=84MHz
    // �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=10000Hz
    TIM_TimeBaseStructure.TIM_Prescaler = 8400 - 1;

    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);    // ��ʼ����ʱ��TIMx, x[2,3,4,5]

    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);    // �����ʱ�������жϱ�־λ

    TIM_ITConfig(BASIC_TIM, TIM_IT_Update, ENABLE);  // ������ʱ�������ж�

    TIM_Cmd(BASIC_TIM, ENABLE);    // ʹ�ܶ�ʱ��
}


/**
  * @brief  ��ʼ��������ʱ����ʱ��1ms����һ���ж�
  * @param  ��
  * @retval ��
  */
void TIMx_Configuration(void)
{
    TIMx_NVIC_Configuration();

    TIM_Mode_Config();
}







