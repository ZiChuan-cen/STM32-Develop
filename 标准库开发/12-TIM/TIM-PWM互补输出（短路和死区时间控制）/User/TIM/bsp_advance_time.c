#include "./TIM/bsp_advance_time.h"

__IO uint16_t ChannelPulse = 127;


/**
  * @brief  配置TIM复用输出PWM时用到的I/O
  * @param  无
  * @retval 无
  */

static void TIMx_GPIO_Config(void) 
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启定时器相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd (ADVANCE_OCPWM_GPIO_CLK |
                        	ADVANCE_OCNPWM_GPIO_CLK|
                        	ADVANCE_BKIN_GPIO_CLK, 
	                        ENABLE); 
  /* 指定引脚复用功能 */
	GPIO_PinAFConfig(ADVANCE_OCPWM_GPIO_PORT,
	                 ADVANCE_OCPWM_PINSOURCE, 
	                 ADVANCE_OCPWM_AF); 
	GPIO_PinAFConfig(ADVANCE_OCNPWM_GPIO_PORT,
	                 ADVANCE_OCNPWM_PINSOURCE,
	                 ADVANCE_OCNPWM_AF); 
	GPIO_PinAFConfig(ADVANCE_BKIN_GPIO_PORT,
	                 ADVANCE_BKIN_PINSOURCE,
	                 ADVANCE_BKIN_AF); 
	
	/* 定时器功能引脚初始化 */															   
	GPIO_InitStructure.GPIO_Pin = ADVANCE_OCPWM_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(ADVANCE_OCPWM_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ADVANCE_OCNPWM_PIN;	
	GPIO_Init(ADVANCE_OCNPWM_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ADVANCE_BKIN_PIN;	
	GPIO_Init(ADVANCE_BKIN_GPIO_PORT, &GPIO_InitStructure);
}


/*
 * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
 * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
 * 另外三个成员是通用定时器和高级定时器才有.
 *-----------------------------------------------------------------------------
 * TIM_Prescaler         都有
 * TIM_CounterMode			 TIMx,x[6,7]没有，其他都有（基本定时器）
 * TIM_Period            都有
 * TIM_ClockDivision     TIMx,x[6,7]没有，其他都有(基本定时器)
 * TIM_RepetitionCounter TIMx,x[1,8]才有(高级定时器)
 *-----------------------------------------------------------------------------
 */
static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	
	
  RCC_APB2PeriphClockCmd(ADVANCE_TIM_CLK, ENABLE);    // 开启TIMx_CLK,x[1,8]  

  /* 累计 TIM_Period个后产生一个更新或者中断*/		
  //当定时器从0计数到1023，即为1024次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Period = 1024-1;
	// 高级控制定时器时钟源TIMxCLK = HCLK=168MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=100000Hz
  TIM_TimeBaseStructure.TIM_Prescaler = 1680-1;	
  
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;    // 采样时钟分频
  
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;    // 计数方式
  
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;    // 重复计数器，没用到	
	
	TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);    // 初始化定时器TIMx, x[1,8]
	
  /*PWM模式配置*/
	//配置为PWM模式1,先输出高电平,	达到比较值的时候再改变电平
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;    //主输出使能	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;    //互补输出使能
  TIM_OCInitStructure.TIM_Pulse = ChannelPulse;    //设置占空比大小
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //主输出高电平有效
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;    //互补输出高电平有效
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;    //主输出在被禁止时为高电平
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;    //互补输出在被禁止时为低电平    
  
  TIM_OC1Init(ADVANCE_TIM, &TIM_OCInitStructure);    //使能通道1  
	
	TIM_OC1PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);    /* 使能通道1重载 */
	

  /*--------------------------------刹车和死区结构体初始化--------------------------------------*/
	/* 自动输出使能，断路、死区时间和锁定配置 */
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
  TIM_BDTRInitStructure.TIM_DeadTime = 11;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(ADVANCE_TIM, &TIM_BDTRInitStructure);	
	
	TIM_Cmd(ADVANCE_TIM, ENABLE);    // 使能定时器	
	
  TIM_CtrlPWMOutputs(ADVANCE_TIM, ENABLE);    /* 主动输出使能 */
}


/**
  * @brief  初始化高级控制定时器
  * @param  无
  * @retval 无
  */
void TIMx_Configuration(void)
{  
	TIMx_GPIO_Config();
	
  TIM_Mode_Config();
}




























