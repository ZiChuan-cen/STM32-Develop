#include "stm32f4xx.h"



int main(void)
{
	/* ��GPIOC�˿ڵ�ʱ�� */
	*(unsigned int *)(0x40023800+0x30) |= (1<<2);
	
  /*  GPIOC ����Ϊ���  */	
	*(unsigned int *)(0x40020800+0x00) &=~  ( (0x03) << (2*6) );
	*(unsigned int *)(0x40020800+0x00) |=  (1 << (2*6) );

	*(unsigned int *)(0x40020800+0x14) |= (1<<6);  /*PC6����ߵ�ƽ*/
	*(unsigned int *)(0x40020800+0x14) &= ~(1<<6);  /*PC6����͵�ƽ*/
} 

//int main(void)
//{
//	/* ��GPIOF�˿ڵ�ʱ�� */
//	RCC_AHB1ENR |= (1<<2);
//	
//  /*  GPIOF ����Ϊ���  */	
//	GPIOC_MODER &=~  ( (0x03) << (2*6) );
//	GPIOC_MODER |=  (1 << (2*6) );

//	GPIOC_ODR |= (1<<6);  /*PF6����ߵ�ƽ*/
//	GPIOC_ODR &= ~(1<<6);  /*PF6����͵�ƽ*/
//	
//}


void SystemInit(void)
{
	/*������Ϊ�գ�Ŀ����Ϊ��ƭ��������������*/
}
