#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./key/bsp_exti.h"

void Delay(__IO u32 nCount)
{
	
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	LED_GPIO_Config();    /* LED �˿ڳ�ʼ�� */
	
	EXTI_Key_Config();    /* EXTI ��ʼ�� */ 	
	
	while(1)                            
	{
	}
}

/*********************************************END OF FILE**********************/

