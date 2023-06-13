/**
  *
  ***************** LED灯对应端口 ************
  * L1  --  PC4
  * L2  --  PC5
  * L3  --  PC6
  * L4  --  PC7
  ********************************************
  * GPIOC 基准地址: 0x40020800
  *
  * RCC 基准地址: 0x40023800
  * RCC_AHB1ENR   偏移地址: 0x30
  *
  * GPIOx_MODER   偏移地址: 0x00    端口模式寄存器
  * GPIOx_OTYPER  偏移地址: 0x04    端口输出类型寄存器
  * GPIOx_OSPEEDR 偏移地址: 0x08    端口输出速度寄存器
  * GPIOx_PUPDR   偏移地址: 0x0C    端口上拉/下拉寄存器
  * GPIOx_ODR     偏移地址: 0x14    端口输出数据寄存器
  * GPIOx_BSRR    偏移地址: 0x18    端口置位/复位寄存器
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
  * @brief  简单的延时函数 
  * @param  无
  * @retval 无
  */
void Delay(__IO uint32_t nCount)	
{
	for(; nCount != 0; nCount--);
}

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    /* 开启 GPIOC 时钟，使用外设时都要先开启它的时钟 */
    RCC_AHB1ENR |= (1 << 2);

    /* 配置推挽输出模式 */

    /* PC6 */
    /*GPIOF MODER6清空*/
    GPIOC_MODER  &= ~(0x03 << (2 * 6));
    /*PF6 MODER6 = 01b 输出模式*/
    GPIOC_MODER |= (1 << 2 * 6);

    /*GPIOF OTYPER6清空*/
    GPIOC_OTYPER &= ~(1 << 1 * 6);
    /*PF6 OTYPER6 = 0b 推挽模式*/
    GPIOC_OTYPER |= (0 << 1 * 6);

    /*GPIOF OSPEEDR6清空*/
    GPIOC_OSPEEDR &= ~(0x03 << 2 * 6);
    /*PF6 OSPEEDR6 = 0b 速率2MHz*/
    GPIOC_OSPEEDR |= (0 << 2 * 6);

    /*GPIOF PUPDR6清空*/
    GPIOC_PUPDR &= ~(0x03 << 2 * 6);
    /*PF6 PUPDR6 = 01b 上拉模式*/
    GPIOC_PUPDR |= (1 << 2 * 6);
	
	while(1)
	{
		/*PF6 BSRR寄存器的 BR6置1，使引脚输出低电平*/
		GPIOC_BSRR |= (1 << 16 << 6);
		Delay(0x10fff0);
		/*PF6 BSRR寄存器的 BS6置1，使引脚输出高电平*/
		GPIOC_BSRR |= (1<<6);
		Delay(0x10fff0);
	}
}



