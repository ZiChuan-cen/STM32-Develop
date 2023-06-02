#include "bsp_led.h"



void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef LED_GPIO_Init;
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	
	HAL_GPIO_Init();
}
