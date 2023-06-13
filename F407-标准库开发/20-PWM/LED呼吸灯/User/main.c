#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_PWM.h"


/**
  * @brief  �򵥵���ʱ����
  * @param  ��
  * @retval ��
  */
void delay(__IO u32 nCount)
{
    for (; nCount != 0; nCount--);
}


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    /* led �˿����� */ 
	LED_GPIO_Config();
	
	/* ��ʱ����ʼ�� */
	GENERAL_TIM_Init();


    while (1)
    {
        LED_RED;
        delay(0xffffff);
        LED_RGBOFF;
        delay(0xffffff);

    }
}


