#include "stm32f4xx.h"
#include "bsp_led.h"



#if 0


P0 = 0xFE;      //总线操作

sbit led1 = p0^0     //位操作
led1 = 0;

GPIOF->ODR |= ( 0<<6 );
GPIOFODR_BITARRD = 0;


#endif

/* 求出位带别名区地址 */
#define BITBAND(addr,bitnum)   ((addr & 0xF0000000)+0x02000000+((addr + 0x000FFFFF)<<5)+(bitnum<<2)) 

/* 对地址进行指针操作 */
#define MEM(addr)    (*(volatile unsigned long*)(addr))

#define BIT_ADDR(addr,bitnum)    MEM(BITBAND(addr,bitnum))

#define GPIOC_ODR_ADDR   (GPIOC_BASE+0x14)

#define PCout(n)         BIT_ADDR(GPIOC_ODR_ADDR,n)





void Delay( uint32_t count )
{
	for( ; count != 0 ; count--);
}


int main(void)
{
	/* 在这里添加代码 */
	
	LED_GPIO_Config();
	
	while(1)
  {
		
		PCout(5) = 1;
		  Delay(0xfffff);
		
		PCout(5) = 0;
		  Delay(0xfffff);
	}
}


