#ifndef __EXTI_H
#define __EXTI_H

#include "stm32f4xx.h"

//按键 KEY1  KEY2 引脚定义
/*******************************************************/
#define KEY1_INT_GPIO_PORT                GPIOA    //KEY1  PA0
#define KEY1_INT_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define KEY1_INT_GPIO_PIN                 GPIO_Pin_0
#define KEY1_INT_EXTI_PORTSOURCE          EXTI_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE           EXTI_PinSource0
#define KEY1_INT_EXTI_LINE                EXTI_Line0
#define KEY1_INT_EXTI_IRQ                 EXTI0_IRQn

#define KEY1_IRQHandler                   EXTI0_IRQHandler



#define KEY2_INT_GPIO_PORT                GPIOE    //KEY2  PE2
#define KEY2_INT_GPIO_CLK                 RCC_AHB1Periph_GPIOE
#define KEY2_INT_GPIO_PIN                 GPIO_Pin_2
#define KEY2_INT_EXTI_PORTSOURCE          EXTI_PortSourceGPIOE
#define KEY2_INT_EXTI_PINSOURCE           EXTI_PinSource2
#define KEY2_INT_EXTI_LINE                EXTI_Line2
#define KEY2_INT_EXTI_IRQ                 EXTI15_10_IRQn

#define KEY2_IRQHandler                   EXTI15_10_IRQHandler

/*******************************************************/

void EXTI_Key_Config(void);

#endif  /* __EXTI_H */
