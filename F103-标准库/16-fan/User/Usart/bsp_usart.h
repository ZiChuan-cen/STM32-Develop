#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h"                  // Device header

#define USART2_GPIO_CLK				RCC_APB2Periph_GPIOA
#define USART2_CLK					RCC_APB1Periph_USART2
#define USART2_TX_PORT				GPIOA
#define USART2_TX_Pin				GPIO_Pin_2	
#define USART2_RX_PORT				GPIOA
#define USART2_RX_Pin				GPIO_Pin_3

void Usart2_Config(void);


void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);

uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);


#endif /* __BSP_USART_H */

