#include "stm32f407.h"



void Delay(unsigned int count)
{
	for(;count!=0;count--);
}	



int main(void)
{
//	/* 打开GPIO端口时钟 */
//	*(unsigned int *)(0x40023800+0x30) |=(1 << 2);
//	
//	/* GPIOA 配置为输出   控制GPIO口方向 */
//	*(unsigned int *)(0x40020800+0x00) &=~ ( (0x03) << (2*6) );
//	*(unsigned int *)(0x40020800+0x00) |=  ( 1 <<(2*6) );
//	
//	*(unsigned int *)(0x40020800+0x14) |=  (1<<6);   /* PC6 输出高电平 */
//	*(unsigned int *)(0x40020800+0x14) &= ~(1<<6);  /* PC6 输出低电平 */
	
	
	
	
	RCC_AHB1ENR |=(1 << 2);        /* 一、打开GPIO端口时钟 */
	
	
	GPIOC->MODER &=~ ( (0x03) << (2*4) );        /* 二、GPIOA 配置为输出   控制GPIO口方向 */
	GPIOC->MODER |=  ( 1 <<(2*4) );
	
	GPIOC->MODER &=~ ( (0x03) << (2*5) );
	GPIOC->MODER |=  ( 1 <<(2*5) );
	
	GPIOC->MODER &=~ ( (0x03) << (2*6) );
	GPIOC->MODER |=  ( 1 <<(2*6) );
	
	GPIOC->MODER &=~ ( (0x03) << (2*7) );
	GPIOC->MODER |=  ( 1 <<(2*7) );
	
	while(1)
	{
	
	GPIOC->ODR |=  (1<<4);   /* PC4 输出高电平 L1*/  
		Delay(0x0ffffe);
	GPIOC->ODR |=  (1<<5);   /* PC5 输出高电平 L2*/
		Delay(0x0ffffe);
	GPIOC->ODR |=  (1<<6);   /* PC6 输出高电平 L3*/
		Delay(0x0ffffe);
	GPIOC->ODR |=  (1<<7);   /* PC7 输出高电平 L4*/
    Delay(0x0ffffe);
		
		
	GPIOC->ODR &= ~(1<<4);   /* PC4 输出低电平 */
		
	GPIOC->ODR &= ~(1<<5);   /* PC5 输出低电平 */
		
	GPIOC->ODR &= ~(1<<6);   /* PC6 输出低电平 */
		
	GPIOC->ODR &= ~(1<<7);   /* PC7 输出低电平 */
	  Delay(0x0ffffe);
	}
	
}	



void SystemInit(void)
{
	
}


