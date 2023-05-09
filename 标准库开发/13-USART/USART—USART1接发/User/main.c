#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"

int main(void)
{	
  Debug_USART_Config();    /*初始化USART 配置模式为 115200 8-N-1，中断接收*/	
	
	Usart_SendString( DEBUG_USART,"这是一个串口中断接收回显实验\n");    /* 发送一个字符串 */
	printf("这是一个串口中断接收回显实验\n");
	
  while(1)
	{	
		
	}	
}


