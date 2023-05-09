#ifndef _STM32F407_H
#define _STM32F407_H
#include <stdint.h>

/* 存放寄存器相关代码 */

 
#define RCC_BASE      ((unsigned int)0x40023800) 

#define GPIOC_BASE    ((unsigned int)0x40020800)

//#define RCC_AHB1ENR    *(unsigned int *)(0x40023800+0x30)
//#define GPIOC_OTYPER   *(unsigned int *)(0x40020800+0x04)
//#define GPIOC_MODER    *(unsigned int *)(0x40020800+0x00)
//#define GPIOC_ODR      *(unsigned int *)(0x40020800+0x14)


#define GPIOC_OTYPER   *(unsigned int *)(GPIOC_BASE+0x04)
#define RCC_AHB1ENR    *(unsigned int *)(RCC_BASE+0x30)
#define GPIOC_MODER    *(unsigned int *)(GPIOC_BASE+0x00)
#define GPIOC_ODR      *(unsigned int *)(GPIOC_BASE+0x14)


/* 外设寄存器结构体定义 */


//typedef unsigned short     int uint16_t;
//typedef unsigned           int uint32_t;

typedef struct
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR; 
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint16_t BSRRL;
	uint16_t BSRRH;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
	  
}GPIO_TypeDef;



#define GPIOC       ((GPIO_TypeDef *)GPIOC_BASE)





#endif /* _STM32F407_H */

