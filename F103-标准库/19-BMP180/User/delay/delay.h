#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

//40MHZ 40000000




void delay_us(uint32_t xus);
void delay_ms(uint32_t xms);
void delay_s(uint32_t xs);

#endif	/* __DELAY_H */
