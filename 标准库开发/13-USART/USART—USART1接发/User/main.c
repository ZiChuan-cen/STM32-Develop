#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"

int main(void)
{	
  Debug_USART_Config();    /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/	
	
	Usart_SendString( DEBUG_USART,"����һ�������жϽ��ջ���ʵ��\n");    /* ����һ���ַ��� */
	printf("����һ�������жϽ��ջ���ʵ��\n");
	
  while(1)
	{	
		
	}	
}


