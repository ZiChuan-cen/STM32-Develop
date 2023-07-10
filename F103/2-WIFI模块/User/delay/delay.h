#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

//40MHZ 40000000

#define delay_1us() {\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
}



extern uint32_t DHT11_Time;


void SysTick_Init(uint32_t tick);
void Delay_us(uint32_t time);
void Delay_ms(uint32_t time);
void Delay(__IO uint32_t nCount);

#endif	/* __DELAY_H */
