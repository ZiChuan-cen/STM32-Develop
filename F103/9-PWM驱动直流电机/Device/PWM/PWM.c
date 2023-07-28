/**
  ******************************************************************************
  * @file    PWM.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-07-28
  * @brief   驱动直流电机相关驱动
  ******************************************************************************
  */


#include "PWM.h"

/**
    * @brief  PWM初始化
    * @pin
    * @param  无
    * @retval 无
    */
void PWM_Init(void)
{
    /************************* 构建结构体 *************************/
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    /************************* 配置GPIO *************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /************************* 配置PWM *************************/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_InternalClockConfig(TIM2);      //采用内部时钟给TIM2提供时钟源
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);


    /************************* 配置输出 *************************/
    TIM_OCStructInit(&TIM_OCInitStructure);     //初始化该结构体对象的成员变量，
    //确保结构体对象的成员变量都已经正确设置

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;

    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);

    TIM_Cmd(TIM2, ENABLE);

}

void PWM_SetCompare3(uint16_t Compare)
{
    TIM_SetCompare3(TIM2, Compare);
}

void PWM_SetCompare4(uint16_t Compare)
{
    TIM_SetCompare4(TIM2, Compare);
}







