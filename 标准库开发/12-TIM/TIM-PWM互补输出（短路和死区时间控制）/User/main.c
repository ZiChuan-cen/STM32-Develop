#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "./TIM/bsp_advance_time.h"
extern __IO uint16_t ChannelPulse;

void Delay( uint32_t count )
{
	for( ; count != 0 ; count--);
}


int main(void)
{
	/* 在这里添加代码 */
	
//	LED_GPIO_Config();  /* LED 端口初始化 */
	
	KEY_GPIO_Config();
	
	TIMx_Configuration();
	
	while(1)
  {       
		/* 扫描KEY1 */
		if( KEY_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
		{
			/* 增大占空比 */
			if(ChannelPulse<960)
				ChannelPulse+=64;
			else
				ChannelPulse=1024;
			TIM_SetCompare1(ADVANCE_TIM,ChannelPulse);
		}   
    /* 扫描KEY2 */
    if( KEY_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON  )
		{
			/* 减小占空比 */
			if(ChannelPulse>=64)
				ChannelPulse-=64;
			else
				ChannelPulse=0;
			TIM_SetCompare1(ADVANCE_TIM,ChannelPulse);
		}   
  }
	

	/* 按键扫描 */
//	while(1)
//  {		
//			if ( KEY_Scan(GPIOE, GPIO_Pin_2) == KEY_ON )    /* 按键K2 */
//    {
//			LED1_TOGGLE;
//		}
//			if ( KEY_Scan(GPIOE, GPIO_Pin_3) == KEY_ON )    /* 按键K3 */
//    {
//			LED2_TOGGLE;
//		}
//  }
}
	
