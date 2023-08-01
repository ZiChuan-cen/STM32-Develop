#ifndef __TRACK_H
#define __TRACK_H


#include "stm32f10x.h"

/* SW2				SW1				SW3				SW4
 *
 * X2				X1				X3				X4
 */



#define Track_X_RCC			RCC_APB2Periph_GPIOB

#define Track_X1_PIN		GPIO_Pin_3
#define Track_X2_PIN		GPIO_Pin_4
#define Track_X3_PIN		GPIO_Pin_4
#define Track_X4_PIN		GPIO_Pin_6

#define Track_X_PORT	GPIOB







#endif  /* __TRACK_H */

