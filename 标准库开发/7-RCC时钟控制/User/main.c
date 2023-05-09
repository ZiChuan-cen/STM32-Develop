#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_clkconfig.h"


void Delay( uint32_t count )
{
	for( ; count != 0 ; count--);
}


int main(void)
{
	/* 程序来到这时，系统的时钟已经由SystemInit这个函数初始化好了 */
	
	USER_SetSysClock();
	
	/* 在这里添加代码 */
	
	LED_GPIO_Config();
	
	while(1)
  {
		GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		Delay(0xfffffe);
		GPIO_SetBits(GPIOC, GPIO_Pin_5);
		Delay(0xfffffe);
	}
}


