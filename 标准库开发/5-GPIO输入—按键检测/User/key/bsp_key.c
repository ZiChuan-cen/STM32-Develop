#include "bsp_key.h"

void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);       
	
	/*ѡ�񰴼�������*/
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN; 

	/*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   

	/*�������Ų�����Ҳ������*/
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 

	/*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);                   
	
	/*ѡ�񰴼�������*/  
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;

	/*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);                 

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


