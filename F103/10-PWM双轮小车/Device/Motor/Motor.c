/**
  ******************************************************************************
  * @file    Motor.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-07-28
  * @brief   ����ֱ������������
  ******************************************************************************
  */


#include "Motor.h"

/**
    * @brief  PWM��ʼ��
    * @pin
    * @param  ��
    * @retval ��
    */
void Motor_Init(void)
{
    /************************* �����ṹ�� *************************/
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    /************************* ����GPIO *************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /************************* ����PWM *************************/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_InternalClockConfig(TIM2);      //�����ڲ�ʱ�Ӹ�TIM2�ṩʱ��Դ
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);


    /************************* ������� *************************/
    TIM_OCStructInit(&TIM_OCInitStructure);     //��ʼ���ýṹ�����ĳ�Ա������
    //ȷ���ṹ�����ĳ�Ա�������Ѿ���ȷ����

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);

    TIM_Cmd(TIM2, ENABLE);

}


void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(TIM2, Compare);
}

void PWM_SetCompare2(uint16_t Compare)
{
    TIM_SetCompare2(TIM2, Compare);
}
void PWM_SetCompare3(uint16_t Compare)
{
    TIM_SetCompare3(TIM2, Compare);
}

void PWM_SetCompare4(uint16_t Compare)
{
    TIM_SetCompare4(TIM2, Compare);
}

void Car_Fowever(void)
{
	PWM_SetCompare1(0);
	PWM_SetCompare2(1000);
	PWM_SetCompare3(1000);
	PWM_SetCompare4(0);
}

void Car_Fowever(void)
{
	PWM_SetCompare1(0);
	PWM_SetCompare2(1000);
	PWM_SetCompare3(1000);
	PWM_SetCompare4(0);
}









