/*
 * @project: 按键检测
 * @key_1 PA0
 * @key_2 PE2
 *
 * @LED_1 PA4 RED
 * @LED_2 PA5 GREEN
 * @LED_3 PA6 BLUE
 * 
 *
*/

#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"

void Delay( uint32_t count )
{
	for( ; count != 0 ; count--);
}


int main(void)
{
	/* 在这里添加代码 */
	
	LED_GPIO_Config();  /* LED 端口初始化 */
	
	KEY_GPIO_Config();

	/* 按键扫描 */
	while(1)
  {		
			if ( KEY_Scan(GPIOA, KEY1_PIN) == KEY_OFF )    /* 按键K1 */
    {
			LED1_TOGGLE;
		}
			if ( KEY_Scan(GPIOE, KEY2_PIN) == KEY_ON )    /* 按键K2 */
    {
			LED2_TOGGLE;
		}
  }
}
	
