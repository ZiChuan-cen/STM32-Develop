#ifndef __ADVANCE_TIM_H
#define	__ADVANCE_TIM_H

#include "stm32f4xx.h"

/* 通用定时器PWM输出 */
/* PWM输出引脚 */
#define GENERAL_OCPWM_PIN             GPIO_Pin_5              
#define GENERAL_OCPWM_GPIO_PORT       GPIOA                      
#define GENERAL_OCPWM_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define GENERAL_OCPWM_PINSOURCE				GPIO_PinSource5
#define GENERAL_OCPWM_AF							GPIO_AF_TIM2

/* 通用定时器 */
#define GENERAL_TIM           		    TIM2
#define GENERAL_TIM_CLK       		    RCC_APB1Periph_TIM2


//输出PWM的频率为84M/{(ARR+1)*(PSC+1)}
//这里配置为100KHZ
#define    GENERAL_TIM_PERIO    (10-1)
#define    GENERAL_TIM_PSC      (84-1)
#define    GENERAL_TIM_CCR1     5



/* 高级控制定时器PWM输入捕获 */
/* PWM输入捕获引脚 */
#define ADVANCE_ICPWM_PIN             GPIO_Pin_6            
#define ADVANCE_ICPWM_GPIO_PORT       GPIOC                      
#define ADVANCE_ICPWM_GPIO_CLK        RCC_AHB1Periph_GPIOC
#define ADVANCE_ICPWM_PINSOURCE				GPIO_PinSource6
#define ADVANCE_ICPWM_AF							GPIO_AF_TIM8
#define ADVANCE_IC1PWM_CHANNEL        TIM_Channel_1
#define ADVANCE_IC2PWM_CHANNEL        TIM_Channel_2

/* 高级控制定时器 */
#define ADVANCE_TIM           		    TIM8
#define ADVANCE_TIM_CLK       		    RCC_APB2Periph_TIM8

/* 捕获/比较中断 */
#define ADVANCE_TIM_IRQn					    TIM8_CC_IRQn
#define ADVANCE_TIM_IRQHandler        TIM8_CC_IRQHandler


//输入捕获能捕获到的最小频率为 168M/{(ARR+1)*(PSC+1)}
//这里配置为1KHZ
#define ADVANCE_TIM_PERIOD    (1000-1)
#define ADVANCE_TIM_PSC       (168-1)


void TIM_PWMOUTPUT_Config(void);
void TIM_PWMINPUT_Config(void);


#endif /* __ADVANCE_TIM_H */


























