#include "stm32f4xx.h"



//int main(void)
//{
//	/* 打开GPIOA端口的时钟 */
//	*(unsigned int *)(0x40023800+0x10) |= (1<<0);
//	
//  /*  GPIOA 配置为输出  */	
//	*(unsigned int *)(0x40020000+0x00) &=~  ( (0x03) << (2*6) );
//	*(unsigned int *)(0x40020000+0x00) |=  (1 << (2*6) );

//	*(unsigned int *)(0x40021400+0x14) |= (1<<3);  /*PF6输出高电平*/
//	*(unsigned int *)(0x40021400+0x14) &= ~(1<<3);  /*PF6输出低电平*/
//} 

int main(void)
{
	/* 打开GPIOE端口的时钟 */
	RCC_AHB1ENR |= (1<<4);
	
  /*  GPIOE 配置为输出  */	
	GPIOE_MODER &=~  ( (0x03) << (2*0) );
	GPIOE_MODER |=  (1 << (2*0) );

	//GPIOE_ODR |= (1<<0);  /*PE0输出高电平*/
	GPIOE_ODR &= ~(1<<0);  /*PE0输出低电平*/
	
}


void SystemInit(void)
{
	/*函数体为空，目的是为了骗过编译器不报错*/
}
