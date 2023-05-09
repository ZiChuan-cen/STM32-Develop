#include "stm32f407_gpio.h"

void GPIO_SetBits(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BSRRL = GPIO_Pin;
}


void GPIO_ResetBits(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->BSRRH = GPIO_Pin;
}


void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00;
	
	/*------------- GPIO Mode Configuration ----------------------*/
	
	for (pinpos = 0x00; pinpos < 16; pinpos++)
  {
		/* 以下运算是为了通过 GPIO_InitStruct->GPIO_Pin 算出引脚号0—15  */
		
		
		
		pos = ((uint32_t)0x01) << pinpos; 
		 /* 经过运算后pos的pinpos位为1，其余为0，与GPIO_Pin_x宏对应。pinpos变量每次循环加1 */
		currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
		/*若currentpin == 1，则GPIO_InitStruct->GPIO_Pin的pinpos位也为1，可知pinpos就是GPIO_InitStruct->GPIO_Pin
		对应的引脚号：0-15*/
		
		/*currentpin == pos时执行初始化*/
		if (currentpin == pos)
    {
			GPIOx->MODER &= ~(3 <<(2 *pinpos));  /*GPIOx端口，MODER寄存器的GPIO_InitStruct->GPIO_Pin对应的引脚，MODER位清空*/
			GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (2 *pinpos));
			/*GPIOx端口，MODER寄存器的GPIO_Pin引脚，MODER位设置"输入/输出/复用输出/模拟"模式*/
			GPIOx->PUPDR &= ~(3 <<(2 *pinpos));  /*GPIOx端口，PUPDR寄存器的GPIO_Pin引脚，PUPDR位清空*/
			GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (2 *pinpos));
			/*GPIOx端口，PUPDR寄存器的GPIO_Pin引脚，PUPDR位设置"上/下拉"模式*/
			
			/*若模式为"输出/复用输出"模式，则设置速度与输出类型*/
			if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
				GPIOx->OSPEEDR  &= ~(3 <<(2 *pinpos));  /*GPIOx端口，OSPEEDR寄存器的GPIO_Pin引脚，OSPEEDR位清空*/
				GPIOx->OSPEEDR  |= (((uint32_t)GPIO_InitStruct->GPIO_Speed) << (2 *pinpos));
				/*GPIOx端口，OSPEEDR寄存器的GPIO_Pin引脚，OPSPEEDR位设置输出速度*/
				GPIOx->OTYPER   &= ~(3 <<(2 *pinpos));  /*GPIOx端口，OTYPER寄存器的GPIO_Pin引脚,OTYPER位清空*/
				GPIOx->OTYPER   |= (((uint32_t)GPIO_InitStruct->GPIO_OType) << (2 *pinpos));
				/*GPIOx端口，OTYPER寄存器的GPIO_Pin引脚,OTYPER位设置"推挽/开漏"输出类型*/
			}
		}
	}
}


