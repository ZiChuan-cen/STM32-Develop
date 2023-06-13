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
	
	
	
	
	RCC_AHB1ENR |=(1 << 0);        /* һ����GPIO�˿�ʱ�� */
	
	
	GPIOA_MODER &=~ ( (0x03) << (2*0) );        /* ����GPIOA ����Ϊ���   ����GPIO�ڷ��� */
	GPIOA_MODER |=  ( 1 <<(2*0) );
	
	GPIOA_MODER &=~ ( (0x03) << (2*1) );
	GPIOA_MODER |=  ( 1 <<(2*1) );
	
	
	GPIOA_MODER &=~ ( (0x03) << (2*2) );
	GPIOA_MODER |=  ( 1 <<(2*2) );
	
	GPIOA_MODER &=~ ( (0x03) << (2*3) );
	GPIOA_MODER |=  ( 1 <<(2*3) );
	
	while(1)
	{
	
	GPIOA_ODR |=  (1<<0);   /* PA0 ����ߵ�ƽ L1*/  
	Delay(0x0ffffe);
		
	GPIOA_ODR |=  (1<<1);   /* PA1 ����ߵ�ƽ L2*/
	Delay(0x0ffffe);
		
	GPIOA_ODR |=  (1<<2);   /* PA2 ����ߵ�ƽ L3*/
	Delay(0x0ffffe);
		
		
		
	GPIOA_ODR &= ~(1<<0);   /* PA0 ����͵�ƽ */
	Delay(0x0ffffe);	
		
	GPIOA_ODR &= ~(1<<1);   /* PA1 ����͵�ƽ */
	Delay(0x0ffffe);	
		
	GPIOA_ODR &= ~(1<<2);   /* PA2 ����͵�ƽ */
	Delay(0x0ffffe);
	
	
	}
}	



void SystemInit(void)
{
	
}
