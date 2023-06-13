#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_PWM.h"


/**
  * @brief  简单的延时函数
  * @param  无
  * @retval 无
  */
void delay(__IO u32 nCount)
{
    for (; nCount != 0; nCount--);
}


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    /* led 端口配置 */ 
	LED_GPIO_Config();
	
	/* 定时器初始化 */
	GENERAL_TIM_Init();


    while (1)
    {
        LED_RED;
        delay(0xffffff);
        LED_RGBOFF;
        delay(0xffffff);

    }
}


