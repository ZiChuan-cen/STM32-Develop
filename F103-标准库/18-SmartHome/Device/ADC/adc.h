#ifndef __ADC_H
#define __ADC_H	

#include "sys.h"
extern int Value;
void Adc_Init(void);
u16 Get_ADC(uint8_t channel);
u16 Get_Value(uint8_t channel);
#endif 
