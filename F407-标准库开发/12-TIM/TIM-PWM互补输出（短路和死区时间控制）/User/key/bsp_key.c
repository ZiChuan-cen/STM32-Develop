#include "bsp_key.h"

void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);     /*开启按键GPIO口的时钟*/  
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;                         /*选择按键的引脚*/  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                    /*设置引脚为输入模式*/  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                /*设置引脚不上拉也不下拉*/  
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);                 /*使用上面的结构体初始化按键*/  
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;                         /*选择按键的引脚*/  
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);                 /*使用上面的结构体初始化按键*/

}

uint8_t KEY_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )    /*检测是否有按键按下 */  
	{	 		
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);    /*等待按键释放 */   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
	
}


