#ifndef _BSP_KEY_H

#define _BSP_KEY_H


#include "stm32f4xx.h"

//Òý½Å¶¨Òå
/*******************************************************/
#define KEY1_PIN                  GPIO_Pin_0                 
#define KEY1_GPIO_PORT            GPIOA                      
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOA

#define KEY2_PIN                  GPIO_Pin_2                 
#define KEY2_GPIO_PORT            GPIOE                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOE
/*******************************************************/

#define KEY_ON     1
#define KEY_OFF    0


void KEY_GPIO_Config(void);
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif  /* _BSP_KEY_H */





