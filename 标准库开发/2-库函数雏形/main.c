#include "stm32f407.h"



void Delay(unsigned int count)
{
	for(;count!=0;count--);
}	



int main(void)
{
//	/* ��GPIO�˿�ʱ�� */
//	*(unsigned int *)(0x40023800+0x30) |=(1 << 2);
//	
//	/* GPIOA ����Ϊ���   ����GPIO�ڷ��� */
//	*(unsigned int *)(0x40020800+0x00) &=~ ( (0x03) << (2*6) );
//	*(unsigned int *)(0x40020800+0x00) |=  ( 1 <<(2*6) );
//	
//	*(unsigned int *)(0x40020800+0x14) |=  (1<<6);   /* PC6 ����ߵ�ƽ */
//	*(unsigned int *)(0x40020800+0x14) &= ~(1<<6);  /* PC6 ����͵�ƽ */
	
	
	
	
	RCC_AHB1ENR |=(1 << 2);        /* һ����GPIO�˿�ʱ�� */
	
	
	GPIOC->MODER &=~ ( (0x03) << (2*4) );        /* ����GPIOA ����Ϊ���   ����GPIO�ڷ��� */
	GPIOC->MODER |=  ( 1 <<(2*4) );
	
	GPIOC->MODER &=~ ( (0x03) << (2*5) );
	GPIOC->MODER |=  ( 1 <<(2*5) );
	
	GPIOC->MODER &=~ ( (0x03) << (2*6) );
	GPIOC->MODER |=  ( 1 <<(2*6) );
	
	GPIOC->MODER &=~ ( (0x03) << (2*7) );
	GPIOC->MODER |=  ( 1 <<(2*7) );
	
	while(1)
	{
	
	GPIOC->ODR |=  (1<<4);   /* PC4 ����ߵ�ƽ L1*/  
		Delay(0x0ffffe);
	GPIOC->ODR |=  (1<<5);   /* PC5 ����ߵ�ƽ L2*/
		Delay(0x0ffffe);
	GPIOC->ODR |=  (1<<6);   /* PC6 ����ߵ�ƽ L3*/
		Delay(0x0ffffe);
	GPIOC->ODR |=  (1<<7);   /* PC7 ����ߵ�ƽ L4*/
    Delay(0x0ffffe);
		
		
	GPIOC->ODR &= ~(1<<4);   /* PC4 ����͵�ƽ */
		
	GPIOC->ODR &= ~(1<<5);   /* PC5 ����͵�ƽ */
		
	GPIOC->ODR &= ~(1<<6);   /* PC6 ����͵�ƽ */
		
	GPIOC->ODR &= ~(1<<7);   /* PC7 ����͵�ƽ */
	  Delay(0x0ffffe);
	}
	
}	



void SystemInit(void)
{
	
}


