#include "stm32f407.h"
#include "stm32f407_gpio.h"

/* �����⺯������ */ 

void Delay(unsigned int count)
{
	for(;count!=0;count--);
}	


int main(void)
{
/**************************************ԭʼ����*************************************************************/
#if 0
	/* ��GPIO�˿�ʱ�� */
	*(unsigned int *)(0x40023800+0x30) |=(1 << 2);
	
	/* GPIOA ����Ϊ���   ����GPIO�ڷ��� */
	*(unsigned int *)(0x40020800+0x00) &=~ ( (0x03) << (2*6) );
	*(unsigned int *)(0x40020800+0x00) |=  ( 1 <<(2*6) );
	
	*(unsigned int *)(0x40020800+0x14) |=  (1<<6);   /* PC6 ����ߵ�ƽ */
	*(unsigned int *)(0x40020800+0x14) &= ~(1<<6);  /* PC6 ����͵�ƽ */
	
/******************************************��׼********************************************************/
#elif 0
	
	RCC_AHB1ENR |=(1 << 2);        /* һ����GPIO�˿�ʱ�� */
	
	GPIOC->MODER &=~ ( (0x03) << (2*4) );        /* ����GPIOC ����Ϊ���   ����GPIO�ڷ��� */
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
		  Delay(0x0ffffe);
		GPIOC->ODR &= ~(1<<5);   /* PC5 ����͵�ƽ */
		  Delay(0x0ffffe);
		GPIOC->ODR &= ~(1<<6);   /* PC6 ����͵�ƽ */
		  Delay(0x0ffffe);
		GPIOC->ODR &= ~(1<<7);   /* PC7 ����͵�ƽ */
	    Delay(0x0ffffe);
	}
	
/****************************************************************************************************************/

/*******************************��������ĳ�ʼ���ṹ��ͱ�д����ĳ�ʼ������*********************************/
	
#elif 1
 
	RCC_AHB1ENR |=(1 << 2);        /* һ����GPIO�˿�ʱ�� */
	
//	GPIOC->MODER &=~ ( (0x03) << (2*5) );      /* ����GPIOA ����Ϊ���   ����GPIO�ڷ��� */
//	GPIOC->MODER |=  ( 1 <<(2*5) );
	
/* c89���﷨��ʽ��������������ڴ����š�{ }������ */

	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStruct);

	
	GPIOC->ODR |= (1<<4);         /* ������GPIO���Ϊ0��1��ODR�Ĵ�������BSRR�Ĵ��� */
	
	while(1)
	{
	
		/* ��д�˿ڵĸ�λ����λ���� */
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		 Delay(0x0ffffe);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		 Delay(0x0ffffe);
		
	}
	
#endif
/***********************************************************************************************************/
	
}	



void SystemInit(void)
{
	
}


