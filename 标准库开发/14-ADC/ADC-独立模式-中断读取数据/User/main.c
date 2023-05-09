#include "stm32f4xx.h"
#include "bsp_debug_usart.h"
#include "bsp_adc.h"


__IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_Vol;


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
    	
			ADC_Vol =(float) ADC_ConvertedValue/4096*(float)3.3; // 读取转换的AD值

      printf("The current AD value = 0x%04X \n", ADC_ConvertedValue); 
      printf("The current AD value = %f V \n\n",ADC_Vol);     

      Delay(0xffffee);  
    }	
}


