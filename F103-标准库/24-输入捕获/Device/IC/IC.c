#include "IC.h"



void IC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    
    /* 开启GPIOA、TIM2时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    /* 配置GPIO */
    //PA1 -- TIM2-CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;             //上拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
    /* 配置时基 */
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                //不分频
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;         //向上计数
    TIM_InitStructure.TIM_Period = 65536 - 1;                         //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_InitStructure.TIM_Prescaler = 72 - 1;                      //设置用来作为 TIMx时钟频率除数的预分频值
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_InitStructure);         //初始化
	
	
	TIM_ICInitTypeDef	TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;			//滤波器
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//输入通道选择
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM2, ENABLE);
	
}


uint32_t IC_GetFreq(void)
{
	return 1000000 / TIM_GetCapture2(TIM2);
}


