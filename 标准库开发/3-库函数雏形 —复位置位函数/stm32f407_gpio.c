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
		/* ����������Ϊ��ͨ�� GPIO_InitStruct->GPIO_Pin ������ź�0��15  */
		
		
		
		pos = ((uint32_t)0x01) << pinpos; 
		 /* ���������pos��pinposλΪ1������Ϊ0����GPIO_Pin_x���Ӧ��pinpos����ÿ��ѭ����1 */
		currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
		/*��currentpin == 1����GPIO_InitStruct->GPIO_Pin��pinposλҲΪ1����֪pinpos����GPIO_InitStruct->GPIO_Pin
		��Ӧ�����źţ�0-15*/
		
		/*currentpin == posʱִ�г�ʼ��*/
		if (currentpin == pos)
    {
			GPIOx->MODER &= ~(3 <<(2 *pinpos));  /*GPIOx�˿ڣ�MODER�Ĵ�����GPIO_InitStruct->GPIO_Pin��Ӧ�����ţ�MODERλ���*/
			GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (2 *pinpos));
			/*GPIOx�˿ڣ�MODER�Ĵ�����GPIO_Pin���ţ�MODERλ����"����/���/�������/ģ��"ģʽ*/
			GPIOx->PUPDR &= ~(3 <<(2 *pinpos));  /*GPIOx�˿ڣ�PUPDR�Ĵ�����GPIO_Pin���ţ�PUPDRλ���*/
			GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (2 *pinpos));
			/*GPIOx�˿ڣ�PUPDR�Ĵ�����GPIO_Pin���ţ�PUPDRλ����"��/����"ģʽ*/
			
			/*��ģʽΪ"���/�������"ģʽ���������ٶ����������*/
			if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
				GPIOx->OSPEEDR  &= ~(3 <<(2 *pinpos));  /*GPIOx�˿ڣ�OSPEEDR�Ĵ�����GPIO_Pin���ţ�OSPEEDRλ���*/
				GPIOx->OSPEEDR  |= (((uint32_t)GPIO_InitStruct->GPIO_Speed) << (2 *pinpos));
				/*GPIOx�˿ڣ�OSPEEDR�Ĵ�����GPIO_Pin���ţ�OPSPEEDRλ��������ٶ�*/
				GPIOx->OTYPER   &= ~(3 <<(2 *pinpos));  /*GPIOx�˿ڣ�OTYPER�Ĵ�����GPIO_Pin����,OTYPERλ���*/
				GPIOx->OTYPER   |= (((uint32_t)GPIO_InitStruct->GPIO_OType) << (2 *pinpos));
				/*GPIOx�˿ڣ�OTYPER�Ĵ�����GPIO_Pin����,OTYPERλ����"����/��©"�������*/
			}
		}
	}
}


