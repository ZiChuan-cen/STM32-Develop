#include "stm32f4xx.h"
#include "bsp_debug_usart.h"
#include "bsp_adc.h"


__IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_Vol;


static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}



int main(void)
{
	
	Debug_USART_Config();    /* ��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ��� */
	
	Rheostat_Init();
  
	
    while (1)
    {
    	
			ADC_Vol =(float) ADC_ConvertedValue/4096*(float)3.3; // ��ȡת����ADֵ

      printf("The current AD value = 0x%04X \n", ADC_ConvertedValue); 
      printf("The current AD value = %f V \n\n",ADC_Vol);     

      Delay(0xffffee);  
    }	
}


