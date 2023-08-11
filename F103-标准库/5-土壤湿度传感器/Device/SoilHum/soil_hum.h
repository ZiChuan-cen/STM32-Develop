#ifndef __SOIL_HUM_H
#define __SOIL_HUM_H

#include "stm32f10x.h"                  // Device header







void Soil_Hum_Init(void);
int Get_Adc_Average(int channel,int count);


#endif /* __SOIL_HUM_H */

