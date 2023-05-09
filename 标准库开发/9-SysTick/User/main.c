#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_systick.h"

void Delay( uint32_t count )
{
	for( ; count != 0 ; count--);
}


int main(void)
{
	/* 在这里添加代码 */
	
	LED_GPIO_Config();
	SysTick_Init();
	
	while(1)
  {
		GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		//Delay_ms(1000);
		SysTick_Delay_Ms(100);
		
		GPIO_SetBits(GPIOC, GPIO_Pin_5);
		//Delay_ms(1000);
		SysTick_Delay_Ms(100);

	}
}


