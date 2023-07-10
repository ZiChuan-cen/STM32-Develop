/**
  ******************************************************************************
  * @file    main.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-13
  * @brief   ������
  ******************************************************************************
  * @attention
  *
  * ƽ̨:STM32 F103 C8T6
  *
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"

/*���º���Ϊ0-180�ȶ���Ƕȿ��Ʋ��Ժ���
	*	PWM �ź���0-180����Ĺ�ϵ��
	*	0.5ms ---------------- 0��
	*	1ms   ---------------- 45��
	*	1.5ms ---------------- 90��
	*	2ms   ---------------- 135��
	*	2.5ms ---------------- 180��
 
	*	���Ƶ����ռ�ձȵļ��㣺
	*	������Ƶ��Ϊ50HZ����PWM����Ϊ20ms��0�ȶ�Ӧ��ռ�ձ�Ϊ2.5%����0.05ms�ĸߵ�ƽ�����
 */
 
//0-180�ȶ�� --> 0-90-180�ȿ��ƺ���
void Server_180_Angle(void)
{
	TIM_SetCompare2(TIM3,5);//0��
	Delay_ms(1000);
	
	TIM_SetCompare2(TIM3,15);//90��
	Delay_ms(1000);	
	
	TIM_SetCompare2(TIM3,25);//180��
	Delay_ms(1000);	
}


int main(void)
{

	Motor_Init(199,7199);
    while (1)
    {
		TIM_SetCompare2(TIM3, 5);
		Delay_ms(2000);
//		TIM_SetCompare2(TIM3, 6);
//		Delay_ms(2000);
//		TIM_SetCompare2(TIM3, 7);
//		Delay_ms(2000);
//		TIM_SetCompare2(TIM3, 8);
//		Delay_ms(2000);
//		TIM_SetCompare2(TIM3, 9);
//		Delay_ms(2000);
//		TIM_SetCompare2(TIM3, 10);
//		Delay_ms(2000);
//		TIM_SetCompare2(TIM3, 15);
//		Delay_ms(2000);
//		TIM_SetCompare2(TIM3, 20);
//		Delay_ms(2000);
		TIM_SetCompare2(TIM3, 25);
		Delay_ms(2000);
    }
}

