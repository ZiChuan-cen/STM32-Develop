#include "timer.h"

extern  uint16_t Num ;

void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_InternalClockConfig(TIM2);

    //���������Ƶ�ʣ�CK_CNT_OV =   CK_CNT / (ARR + 1)
    //                          =   CK_PSC / (PSC + 1)(ARR + 1)
    //��ʱƵ�� = 72M / (PSC + 1)(ARR + 1)
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //һ��Ƶ
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;     //���ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;   //���ڣ�ARR�Զ���װ����ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;     //PSCԤ��Ƶ����ֵ
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;        //�ظ���������ֵ

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    //�ֶ������жϱ�־λ����ֹϵͳ��ʼ��������¼�������ж�ͬʱ����
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);


    //ʹ���жϣ������ж���NVIC��ͨ·
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //TIM_IT_Update �����ж�

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef    NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //��Ӧ���ȼ�

    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}


//����ʱ�����������ж�ʱ���ú����Զ�ִ��
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        Num++;
//      if ((Num % 5) == 0)
//      {
//          Num +=3;
//      }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);     //�����־λ
    }

}
