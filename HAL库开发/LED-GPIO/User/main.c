/**
  *
  ***************** LED�ƶ�Ӧ�˿� ************
  * L1  --  PC4
  * L2  --  PC5
  * L3  --  PC6
  * L4  --  PC7
  ********************************************
  * GPIOC ��׼��ַ: 0x40020800
  *
  * RCC ��׼��ַ: 0x40023800
  * RCC_AHB1ENR   ƫ�Ƶ�ַ: 0x30
  *
  * GPIOx_MODER   ƫ�Ƶ�ַ: 0x00    �˿�ģʽ�Ĵ���
  * GPIOx_OTYPER  ƫ�Ƶ�ַ: 0x04    �˿�������ͼĴ���
  * GPIOx_OSPEEDR ƫ�Ƶ�ַ: 0x08    �˿�����ٶȼĴ���
  * GPIOx_PUPDR   ƫ�Ƶ�ַ: 0x0C    �˿�����/�����Ĵ���
  * GPIOx_ODR     ƫ�Ƶ�ַ: 0x14    �˿�������ݼĴ���
  * GPIOx_BSRR    ƫ�Ƶ�ַ: 0x18    �˿���λ/��λ�Ĵ���
  */
#include "stm32f407xx.h"

/****************************************************/
#define RCC_AHB1ENR     (*(unsigned int*)(0x40023800 + 0x30))

#define GPIOC_MODER     (*(unsigned int*)(0x40020800 + 0x00))
#define GPIOC_OTYPER    (*(unsigned int*)(0x40020800 + 0x04))
#define GPIOC_OSPEEDR   (*(unsigned int*)(0x40020800 + 0x08))
#define GPIOC_PUPDR     (*(unsigned int*)(0x40020800 + 0x0C))
#define GPIOC_ODR       (*(unsigned int*)(0x40020800 + 0x14))
#define GPIOC_BSRR      (*(unsigned int*)(0x40020800 + 0x18))



/**
  * @brief  �򵥵���ʱ���� 
  * @param  ��
  * @retval ��
  */
void Delay(__IO uint32_t nCount)	
{
	for(; nCount != 0; nCount--);
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    /* ���� GPIOC ʱ�ӣ�ʹ������ʱ��Ҫ�ȿ�������ʱ�� */
    RCC_AHB1ENR |= (1 << 2);

    /* �����������ģʽ */

    /* PC6 */
    /*GPIOF MODER6���*/
    GPIOC_MODER  &= ~(0x03 << (2 * 6));
    /*PF6 MODER6 = 01b ���ģʽ*/
    GPIOC_MODER |= (1 << 2 * 6);

    /*GPIOF OTYPER6���*/
    GPIOC_OTYPER &= ~(1 << 1 * 6);
    /*PF6 OTYPER6 = 0b ����ģʽ*/
    GPIOC_OTYPER |= (0 << 1 * 6);

    /*GPIOF OSPEEDR6���*/
    GPIOC_OSPEEDR &= ~(0x03 << 2 * 6);
    /*PF6 OSPEEDR6 = 0b ����2MHz*/
    GPIOC_OSPEEDR |= (0 << 2 * 6);

    /*GPIOF PUPDR6���*/
    GPIOC_PUPDR &= ~(0x03 << 2 * 6);
    /*PF6 PUPDR6 = 01b ����ģʽ*/
    GPIOC_PUPDR |= (1 << 2 * 6);
	
	while(1)
	{
		/*PF6 BSRR�Ĵ����� BR6��1��ʹ��������͵�ƽ*/
		GPIOC_BSRR |= (1 << 16 << 6);
		Delay(0x10fff0);
		/*PF6 BSRR�Ĵ����� BS6��1��ʹ��������ߵ�ƽ*/
		GPIOC_BSRR |= (1<<6);
		Delay(0x10fff0);
	}
}



