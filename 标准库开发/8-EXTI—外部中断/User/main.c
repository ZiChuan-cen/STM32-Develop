#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./key/bsp_exti.h"

void Delay(__IO u32 nCount)
{
	
}

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	LED_GPIO_Config();    /* LED 端口初始化 */
	
	EXTI_Key_Config();    /* EXTI 初始化 */ 	
	
	while(1)                            
	{
	}
}

/*********************************************END OF FILE**********************/

