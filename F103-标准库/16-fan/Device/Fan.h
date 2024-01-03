#ifndef __FAN_H
#define __FAN_H

#include "stm32f10x.h"                  // Device header



#define Fan_GPIO_CLK				RCC_APB2Periph_GPIOA
#define Fan_PORT					GPIOA
#define Fan_Pin						GPIO_Pin_5

void Fan_Init(void);
void Fan_ON(void);
void Fan_OFF(void);



#endif /* __FAN_H */
