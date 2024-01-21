#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h"                  // Device header

#define USART1_GPIO_CLK				RCC_APB2Periph_GPIOA
#define USART1_CLK					RCC_APB2Periph_USART1
#define USART1_TX_PORT				GPIOA
#define USART1_TX_Pin				GPIO_Pin_9
#define USART1_RX_PORT				GPIOA
#define USART1_RX_Pin				GPIO_Pin_10


#define USART2_GPIO_CLK				RCC_APB2Periph_GPIOA
#define USART2_CLK					RCC_APB1Periph_USART2
#define USART2_TX_PORT				GPIOA
#define USART2_TX_Pin				GPIO_Pin_2	
#define USART2_RX_PORT				GPIOA
#define USART2_RX_Pin				GPIO_Pin_3


#define	USART3_GPIO_CLK				RCC_APB2Periph_GPIOB
#define USART3_CLK					RCC_APB1Periph_USART3
#define USART3_TX_PORT				GPIOB
#define USART3_TX_Pin				GPIO_Pin_10
#define USART3_RX_PORT				GPIOB
#define USART3_RX_Pin				GPIO_Pin_11



void Usart1_Config(void);
void Usart2_Config(void);
void Usart3_Config(void);


#endif /* __BSP_USART_H */

