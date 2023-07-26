#ifndef __OLED_H
#define __OLED_H


#include "stm32f10x.h"                  // Device header

/*“˝Ω≈≈‰÷√*/
#define OLED_W_D0(x)        GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(x))
#define OLED_W_D1(x)        GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)(x))
#define OLED_W_RES(x)       GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)(x))
#define OLED_W_DC(x)        GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)(x))
#define OLED_W_CS(x)        GPIO_WriteBit(GPIOA, GPIO_Pin_8, (BitAction)(x))



void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowChinese(uint8_t Line, uint8_t Column, uint8_t num);
void OLED_BMP(int i);

#endif /* __OLED_H */

