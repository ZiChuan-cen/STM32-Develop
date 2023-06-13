#include "stm32f407.h"
#include "stm32f407_gpio.h"

/* 构建库函数雏形 */ 

void Delay(unsigned int count)
{
	for(;count!=0;count--);
}	


int main(void)
{
/**************************************原始代码*************************************************************/
#if 0
	/* 打开GPIO端口时钟 */
	*(unsigned int *)(0x40023800+0x30) |=(1 << 2);
	
	/* GPIOA 配置为输出   控制GPIO口方向 */
	*(unsigned int *)(0x40020800+0x00) &=~ ( (0x03) << (2*6) );
	*(unsigned int *)(0x40020800+0x00) |=  ( 1 <<(2*6) );
	
	*(unsigned int *)(0x40020800+0x14) |=  (1<<6);   /* PC6 输出高电平 */
	*(unsigned int *)(0x40020800+0x14) &= ~(1<<6);  /* PC6 输出低电平 */
	
/******************************************基准********************************************************/
#elif 0
	
	RCC_AHB1ENR |=(1 << 2);        /* 一、打开GPIO端口时钟 */
	
	GPIOC->MODER &=~ ( (0x03) << (2*4) );        /* 二、GPIOC 配置为输出   控制GPIO口方向 */
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
		  Delay(0x0ffffe);
		GPIOC->ODR &= ~(1<<5);   /* PC5 输出低电平 */
		  Delay(0x0ffffe);
		GPIOC->ODR &= ~(1<<6);   /* PC6 输出低电平 */
		  Delay(0x0ffffe);
		GPIOC->ODR &= ~(1<<7);   /* PC7 输出低电平 */
	    Delay(0x0ffffe);
	}
	
/****************************************************************************************************************/

/*******************************定义外设的初始化结构体和编写外设的初始化函数*********************************/
	
#elif 1
 
	RCC_AHB1ENR |=(1 << 2);        /* 一、打开GPIO端口时钟 */
	
//	GPIOC->MODER &=~ ( (0x03) << (2*5) );      /* 二、GPIOA 配置为输出   控制GPIO口方向 */
//	GPIOC->MODER |=  ( 1 <<(2*5) );
	
/* c89的语法格式，变量必须紧跟在大括号“{ }”后面 */

	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStruct);

	
	GPIOC->ODR |= (1<<4);         /* 三、让GPIO输出为0或1，ODR寄存器或者BSRR寄存器 */
	
	while(1)
	{
	
		/* 编写端口的复位和置位函数 */
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


