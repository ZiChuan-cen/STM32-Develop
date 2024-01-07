#ifndef __DHT_H
#define __DHT_H	 
#include "sys.h"

/************************ DHT11 �������Ͷ���******************************/
typedef struct
{
		uint8_t  humi_high8bit;		//ԭʼ���ݣ�ʪ�ȸ�8λ
		uint8_t  humi_low8bit;	 	//ԭʼ���ݣ�ʪ�ȵ�8λ
		uint8_t  temp_high8bit;	 	//ԭʼ���ݣ��¶ȸ�8λ
		uint8_t  temp_low8bit;	 	//ԭʼ���ݣ��¶ȸ�8λ
		uint8_t  check_sum;	 	    //У���
		float    humidity;        //ʵ��ʪ��
		float    temperature;     //ʵ���¶�  
} DHT11_Data_TypeDef;


/* �궨�� -------------------------------------------------------------------*/
/***********************   DHT11 �������Ŷ���  **************************/
#define DHT11_Dout_GPIO_CLK_ENABLE()              RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE)
#define DHT11_Dout_PORT                           GPIOB
#define DHT11_Dout_PIN                            GPIO_Pin_12

/***********************   DHT11 �����궨��  ****************************/
#define DHT11_Dout_LOW()                          GPIO_ResetBits(DHT11_Dout_PORT,DHT11_Dout_PIN) 
#define DHT11_Dout_HIGH()                         GPIO_SetBits(DHT11_Dout_PORT,DHT11_Dout_PIN)
#define DHT11_Data_IN()	                          GPIO_ReadInputDataBit(DHT11_Dout_PORT,DHT11_Dout_PIN)



/* ��չ���� ------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
void DHT11_Init( void );
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef * DHT11_Data);
#endif

