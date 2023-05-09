#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_clkconfig.h"


void Delay( uint32_t count )
{
	for( ; count != 0 ; count--);
}


int main(void)
{
	/* ����������ʱ��ϵͳ��ʱ���Ѿ���SystemInit���������ʼ������ */
	
	USER_SetSysClock();
	
	/* ��������Ӵ��� */
	
	LED_GPIO_Config();
	
	while(1)
  {
		GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		Delay(0xfffffe);
		GPIO_SetBits(GPIOC, GPIO_Pin_5);
		Delay(0xfffffe);
	}
}


