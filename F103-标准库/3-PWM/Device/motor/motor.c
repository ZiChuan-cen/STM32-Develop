/**
  ******************************************************************************
  * @file    motor.c
  * @author  zichuan
  * @date    2023-07-10
  * @brief   ������ƣ�ʹ��ͨ�ö�ʱ��TIM3
  ******************************************************************************
  */

#include "motor.h"


void Motor_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    /* ����GPIOB��TIM����ӳ��ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* ��ӳ�䶨ʱ��*/
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    /* ����GPIO */
    //PB5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //�����������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* ���ö�ʱ�� */
    TIM_InitStructure.TIM_ClockDivision = 0;                //����Ƶ
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;         //���ϼ���
    TIM_InitStructure.TIM_Period = arr;                         //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_InitStructure.TIM_Prescaler = psc;                      //����������Ϊ TIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_InitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_InitStructure);         //��ʼ��

    //����PWM
    TIM_OCStructInit(&TIM_OCInitStructure);             //��Ϊ�ṹ���Ա��һ����ʼֵ���������޸��������
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                   //����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;       //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0;              //CCR   ����ռ�ձȴ�С����������compare��������һ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;           //���ͨ����ƽ��������
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;          //���ͨ�����е�ƽ��������

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);                                     //��ʼ��ͨ��2
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);                        //ʹ��ͨ��2���

    TIM_Cmd(TIM3, ENABLE);              //ʹ��TIM3







}






