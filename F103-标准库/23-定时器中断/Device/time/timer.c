#include "timer.h"

extern  uint16_t Num ;

void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_InternalClockConfig(TIM2);

    //计数器溢出频率：CK_CNT_OV =   CK_CNT / (ARR + 1)
    //                          =   CK_PSC / (PSC + 1)(ARR + 1)
    //定时频率 = 72M / (PSC + 1)(ARR + 1)
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //一分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;     //向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;   //周期，ARR自动重装器的值
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;     //PSC预分频器的值
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;        //重复计数器的值

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    //手动更新中断标志位，防止系统初始化后更新事件与更新中断同时发生
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);


    //使能中断，开启中断至NVIC的通路
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //TIM_IT_Update 更新中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef    NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //中断通道
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //响应优先级

    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}


//当定时器产生更新中断时，该函数自动执行
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        Num++;
//      if ((Num % 5) == 0)
//      {
//          Num +=3;
//      }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);     //清除标志位
    }

}
