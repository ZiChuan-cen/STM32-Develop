/* 存放寄存器相关代码 */

 
#define RCC_BASE      ((unsigned int)0x40023800) 

#define GPIOA_BASE    ((unsigned int)0x40020000)

//#define RCC_AHB1ENR    *(unsigned int *)(0x40023800+0x30)
//	
//#define GPIOC_OTYPER   *(unsigned int *)(0x40020800+0x04)
//
//#define GPIOC_MODER    *(unsigned int *)(0x40020800+0x00)
//	
//#define GPIOC_ODR      *(unsigned int *)(0x40020800+0x14)


#define GPIOA_OTYPER   *(unsigned int *)(GPIOA_BASE+0x04)

#define RCC_AHB1ENR    *(unsigned int *)(RCC_BASE+0x30)

#define GPIOA_MODER    *(unsigned int *)(GPIOA_BASE+0x00)
	
#define GPIOA_ODR      *(unsigned int *)(GPIOA_BASE+0x14)

