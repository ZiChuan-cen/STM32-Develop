#ifndef __IO_H
#define __IO_H	 
#include "sys.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)
#define KEY2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define KEY4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)

#define IR GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)

#define BEEP PCout(13)
#define Waring_LED PBout(11)
#define WiFi_LED PAout(11)

u8 key_scan(void);

void IO_Init(void);

#endif

