#include "bsp_key.h"

void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);     /*��������GPIO�ڵ�ʱ��*/  
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;                         /*ѡ�񰴼�������*/  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                    /*��������Ϊ����ģʽ*/  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                /*�������Ų�����Ҳ������*/  
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);                 /*ʹ������Ľṹ���ʼ������*/  
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;                         /*ѡ�񰴼�������*/  
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);                 /*ʹ������Ľṹ���ʼ������*/

}

uint8_t KEY_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )    /*����Ƿ��а������� */  
	{	 		
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);    /*�ȴ������ͷ� */   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
	
}


