#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_usart.h"

void Delay( uint32_t count )
{
	for( ; count != 0 ; count--);
}


int main(void)
{
	/* 在这里添加代码 */
  Debug_USART_Config();
  //Usart_SendByte( DEBUG_USART, 'a');
	//Usart_SendString( DEBUG_USART, "stm32f407串口实验\n");
	printf("stm32f407串口实验\n");
	
	
//LED_GPIO_Config();
	
	while(1)
  {
//		GPIO_ResetBits(GPIOC, GPIO_Pin_5);
//		Delay(0xfffffe);
//		GPIO_SetBits(GPIOC, GPIO_Pin_5);
//		Delay(0xfffffe);
	}
}


