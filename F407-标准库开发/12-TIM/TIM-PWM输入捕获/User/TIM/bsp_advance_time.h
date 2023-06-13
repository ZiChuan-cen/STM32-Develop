#ifndef __ADVANCE_TIM_H
#define	__ADVANCE_TIM_H

#include "stm32f4xx.h"

/* ͨ�ö�ʱ��PWM��� */
/* PWM������� */
#define GENERAL_OCPWM_PIN             GPIO_Pin_5              
#define GENERAL_OCPWM_GPIO_PORT       GPIOA                      
#define GENERAL_OCPWM_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define GENERAL_OCPWM_PINSOURCE				GPIO_PinSource5
#define GENERAL_OCPWM_AF							GPIO_AF_TIM2

/* ͨ�ö�ʱ�� */
#define GENERAL_TIM           		    TIM2
#define GENERAL_TIM_CLK       		    RCC_APB1Periph_TIM2


//���PWM��Ƶ��Ϊ84M/{(ARR+1)*(PSC+1)}
//��������Ϊ100KHZ
#define    GENERAL_TIM_PERIO    (10-1)
#define    GENERAL_TIM_PSC      (84-1)
#define    GENERAL_TIM_CCR1     5



/* �߼����ƶ�ʱ��PWM���벶�� */
/* PWM���벶������ */
#define ADVANCE_ICPWM_PIN             GPIO_Pin_6            
#define ADVANCE_ICPWM_GPIO_PORT       GPIOC                      
#define ADVANCE_ICPWM_GPIO_CLK        RCC_AHB1Periph_GPIOC
#define ADVANCE_ICPWM_PINSOURCE				GPIO_PinSource6
#define ADVANCE_ICPWM_AF							GPIO_AF_TIM8
#define ADVANCE_IC1PWM_CHANNEL        TIM_Channel_1
#define ADVANCE_IC2PWM_CHANNEL        TIM_Channel_2

/* �߼����ƶ�ʱ�� */
#define ADVANCE_TIM           		    TIM8
#define ADVANCE_TIM_CLK       		    RCC_APB2Periph_TIM8

/* ����/�Ƚ��ж� */
#define ADVANCE_TIM_IRQn					    TIM8_CC_IRQn
#define ADVANCE_TIM_IRQHandler        TIM8_CC_IRQHandler


//���벶���ܲ��񵽵���СƵ��Ϊ 168M/{(ARR+1)*(PSC+1)}
//��������Ϊ1KHZ
#define ADVANCE_TIM_PERIOD    (1000-1)
#define ADVANCE_TIM_PSC       (168-1)


void TIM_PWMOUTPUT_Config(void);
void TIM_PWMINPUT_Config(void);


#endif /* __ADVANCE_TIM_H */


























