/*
 * @project: �������
 * @key_1 PA0
 * @key_2 PE2
 *
 * @LED_1 PA4 RED
 * @LED_2 PA5 GREEN
 * @LED_3 PA6 BLUE
 * 
 *
*/

#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"

void Delay( uint32_t count )
{
	for( ; count != 0 ; count--);
}


int main(void)
{
	/* ��������Ӵ��� */
	
	LED_GPIO_Config();  /* LED �˿ڳ�ʼ�� */
	
	KEY_GPIO_Config();

	/* ����ɨ�� */
	while(1)
  {		
			if ( KEY_Scan(GPIOA, KEY1_PIN) == KEY_OFF )    /* ����K1 */
    {
			LED1_TOGGLE;
		}
			if ( KEY_Scan(GPIOE, KEY2_PIN) == KEY_ON )    /* ����K2 */
    {
			LED2_TOGGLE;
		}
  }
}
	
