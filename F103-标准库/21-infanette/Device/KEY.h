#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"                  // Device header


#define Key1                                    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define Key2                                    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define Key3                                    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)





extern uint8_t Keyvalue;
void Key_Init(void);
void Key_Scan(void);



#endif

