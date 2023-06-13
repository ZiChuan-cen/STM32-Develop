#include "stm32f4xx.h"



int main(void)
{
	/* 打开GPIOC端口的时钟 */
	*(unsigned int *)(0x40023800+0x30) |= (1<<2);
	
  /*  GPIOC 配置为输出  */	
	*(unsigned int *)(0x40020800+0x00) &=~  ( (0x03) << (2*6) );
	*(unsigned int *)(0x40020800+0x00) |=  (1 << (2*6) );

	*(unsigned int *)(0x40020800+0x14) |= (1<<6);  /*PC6输出高电平*/
	*(unsigned int *)(0x40020800+0x14) &= ~(1<<6);  /*PC6输出低电平*/
} 

//int main(void)
//{
//	/* 打开GPIOF端口的时钟 */
//	RCC_AHB1ENR |= (1<<2);
//	
//  /*  GPIOF 配置为输出  */	
//	GPIOC_MODER &=~  ( (0x03) << (2*6) );
//	GPIOC_MODER |=  (1 << (2*6) );

//	GPIOC_ODR |= (1<<6);  /*PF6输出高电平*/
//	GPIOC_ODR &= ~(1<<6);  /*PF6输出低电平*/
//	
//}


void SystemInit(void)
{
	/*函数体为空，目的是为了骗过编译器不报错*/
}
