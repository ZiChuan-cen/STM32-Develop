/**
  ******************************************************************************
  * @file    motor.c
  * @author  zichuan
  * @date    2023-07-10
  * @brief   舵机控制，使用通用定时器TIM3
  ******************************************************************************
  */

#include "motor.h"


void Motor_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    /* 开启GPIOB、TIM、重映射时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* 重映射定时器*/
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    /* 配置GPIO */
    //PB5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //复用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* 配置定时器 */
    TIM_InitStructure.TIM_ClockDivision = 0;                //不分频
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;         //向上计数
    TIM_InitStructure.TIM_Period = arr;                         //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_InitStructure.TIM_Prescaler = psc;                      //设置用来作为 TIMx时钟频率除数的预分频值
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_InitStructure);         //初始化

    //配置PWM
    TIM_OCStructInit(&TIM_OCInitStructure);             //先为结构体成员赋一个初始值，在下面修改所需变量
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                   //配置为PWM模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;       //比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;              //CCR   设置占空比大小，在主函数compare中又设置一遍
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;           //输出通道电平极性配置
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;          //输出通道空闲电平极性配置

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);                                     //初始化通道2
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);                        //使能通道2输出

    TIM_Cmd(TIM3, ENABLE);              //使能TIM3







}






