/**
  ******************************************************************************
  * @file    main.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-13
  * @brief   主函数
  ******************************************************************************
  * @attention
  *
  * 平台:STM32 F103 C8T6
  *
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"

/*以下函数为0-180度舵机角度控制测试函数
	*	PWM 信号与0-180舵机的关系：
	*	0.5ms ---------------- 0度
	*	1ms   ---------------- 45度
	*	1.5ms ---------------- 90度
	*	2ms   ---------------- 135度
	*	2.5ms ---------------- 180度
 
	*	舵机频率与占空比的计算：
	*	设舵机的频率为50HZ，则PWM周期为20ms，0度对应的占空比为2.5%，即0.05ms的高电平输出。
 */
 
//0-180度舵机 --> 0-90-180度控制函数
void Server_180_Angle(void)
{
	TIM_SetCompare2(TIM3,5);//0度
	Delay_ms(1000);
	
	TIM_SetCompare2(TIM3,15);//90度
	Delay_ms(1000);	
	
	TIM_SetCompare2(TIM3,25);//180度
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

