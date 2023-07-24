#ifndef __BH1750_H
#define __BH1750_H

#include "stm32f10x.h"

#define uchar unsigned char 
#define uint  unsigned int
	
extern uchar    BUF[8];                         //�������ݻ�����      	
extern int     dis_data;                        //����		
extern int   mcy;             					//��ʾ��λ��־λ

#define	  SlaveAddress   0x46   
/* ����������IIC�����еĴӵ�ַ,
   ����ALT  ADDRESS��ַ���Ų�ͬ�޸�
   ALT  ADDRESS���Žӵ�ʱ��ַΪ0x46
   �ӵ�Դʱ��ַΪ0xB8 */


#define SCL_High	GPIO_SetBits(GPIOB,GPIO_Pin_6) 
#define SCL_Low		GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define SDA_High	GPIO_SetBits(GPIOB,GPIO_Pin_7) 
#define SDA_Low		GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define sda   			GPIO_Pin_7
#define scl  	 		GPIO_Pin_6
#define bh1750_PORT 	GPIOB
#define BH1750_CLK		RCC_APB2Periph_GPIOB


void BH1750_Init(void);
float BH1750_Read_Value(void);
void BH1750_Write_Com(uchar REG_Address);		//д��ָ��
void BH1750_Read_Com(void);					//��ȡָ��


#endif /* __BH1750_H */

