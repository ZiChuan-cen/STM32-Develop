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
	
	
	
	
	RCC_AHB1ENR |=(1 << 0);        /* 一、打开GPIO端口时钟 */
	
	
	GPIOA_MODER &=~ ( (0x03) << (2*0) );        /* 二、GPIOA 配置为输出   控制GPIO口方向 */
	GPIOA_MODER |=  ( 1 <<(2*0) );
	
	GPIOA_MODER &=~ ( (0x03) << (2*1) );
	GPIOA_MODER |=  ( 1 <<(2*1) );
	
	
	GPIOA_MODER &=~ ( (0x03) << (2*2) );
	GPIOA_MODER |=  ( 1 <<(2*2) );
	
	GPIOA_MODER &=~ ( (0x03) << (2*3) );
	GPIOA_MODER |=  ( 1 <<(2*3) );
	
	while(1)
	{
	
	GPIOA_ODR |=  (1<<0);   /* PA0 输出高电平 L1*/  
	Delay(0x0ffffe);
		
	GPIOA_ODR |=  (1<<1);   /* PA1 输出高电平 L2*/
	Delay(0x0ffffe);
		
	GPIOA_ODR |=  (1<<2);   /* PA2 输出高电平 L3*/
	Delay(0x0ffffe);
		
		
		
	GPIOA_ODR &= ~(1<<0);   /* PA0 输出低电平 */
	Delay(0x0ffffe);	
		
	GPIOA_ODR &= ~(1<<1);   /* PA1 输出低电平 */
	Delay(0x0ffffe);	
		
	GPIOA_ODR &= ~(1<<2);   /* PA2 输出低电平 */
	Delay(0x0ffffe);
	
	
	}
}	



void SystemInit(void)
{
	
}
