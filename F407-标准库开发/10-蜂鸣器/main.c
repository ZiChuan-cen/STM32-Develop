#include "stm32f4xx.h"



//int main(void)
//{
//	/* ��GPIOA�˿ڵ�ʱ�� */
//	*(unsigned int *)(0x40023800+0x10) |= (1<<0);
//	
//  /*  GPIOA ����Ϊ���  */	
//	*(unsigned int *)(0x40020000+0x00) &=~  ( (0x03) << (2*6) );
//	*(unsigned int *)(0x40020000+0x00) |=  (1 << (2*6) );

//	*(unsigned int *)(0x40021400+0x14) |= (1<<3);  /*PF6����ߵ�ƽ*/
//	*(unsigned int *)(0x40021400+0x14) &= ~(1<<3);  /*PF6����͵�ƽ*/
//} 

int main(void)
{
	/* ��GPIOE�˿ڵ�ʱ�� */
	RCC_AHB1ENR |= (1<<4);
	
  /*  GPIOE ����Ϊ���  */	
	GPIOE_MODER &=~  ( (0x03) << (2*0) );
	GPIOE_MODER |=  (1 << (2*0) );

	//GPIOE_ODR |= (1<<0);  /*PE0����ߵ�ƽ*/
	GPIOE_ODR &= ~(1<<0);  /*PE0����͵�ƽ*/
	
}


void SystemInit(void)
{
	/*������Ϊ�գ�Ŀ����Ϊ��ƭ��������������*/
}
