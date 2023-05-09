#include "stm32f4xx.h"
#include "bsp_debug_usart.h"
#include "bsp_adc.h"


// ADC转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[RHEOSTAT_NOFCHANEL]={0}; 


static void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}



int main(void)
{
	
	Debug_USART_Config();    /* 初始化USART 配置模式为 115200 8-N-1，中断接收 */  
	
	Rheostat_Init();
	
	while (1)
	{
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*(float)3.3;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*(float)3.3;
		ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*(float)3.3;
		
		printf("\r\n CH1_C3 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
		printf("\r\n CH2_PA4 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
		printf("\r\n CH3_PA6 value = %f V \r\n",ADC_ConvertedValueLocal[2]);
		
		printf("\r\n\r\n");
		Delay(0xffffff);  
	}	
}


