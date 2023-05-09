/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   控制多彩流水灯
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_basic_tim.h"



/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    /* LED 端口初始化 */
    LED_GPIO_Config();

    TIMx_Configuration();

    while (1)
    {

    }
}


/*********************************************END OF FILE**********************/

