#include "stm32f4xx.h"
#include "bsp_debug_usart.h"
#include "bsp_adc.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint32_t ADC_ConvertedValue[3];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[3]; 

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
    Delay(0xffffee);  
    
	  
	//ǿ��ת��Ϊ16λ,����ֻ���� ��16λ
    ADC_ConvertedValueLocal[0] =(float)((uint16_t)ADC_ConvertedValue[0]*3.3/4096); 
    ADC_ConvertedValueLocal[1] =(float)((uint16_t)ADC_ConvertedValue[1]*3.3/4096);
    ADC_ConvertedValueLocal[2] =(float)((uint16_t)ADC_ConvertedValue[2]*3.3/4096);
    
    printf("\r\n The current AD value = 0x%08X \r\n", ADC_ConvertedValue[0]); 
    printf("\r\n The current AD value = 0x%08X \r\n", ADC_ConvertedValue[1]); 
    printf("\r\n The current AD value = 0x%08X \r\n", ADC_ConvertedValue[2]); 
    
    printf("\r\n The current ADC1 value = %f V \r\n",ADC_ConvertedValueLocal[0]); 
    printf("\r\n The current ADC3 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
    printf("\r\n The current ADC2 value = %f V \r\n",ADC_ConvertedValueLocal[2]);
  }
	
		
}


