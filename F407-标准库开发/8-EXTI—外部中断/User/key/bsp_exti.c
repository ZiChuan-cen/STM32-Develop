#include "bsp_exti.h"


static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置NVIC为优先级组1 */
	/* 提示 NVIC_PriorityGroupConfig() 在整个工程只需要调用一次来配置优先级分组*/
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  
  
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;      /* 配置中断源：按键1 */  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    /* 配置抢占优先级：1 */  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;           /* 配置子优先级：1 */  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              /* 使能中断通道 */
  NVIC_Init(&NVIC_InitStructure);
  
  /* 配置中断源：按键2，其他使用上面相关配置 */  
  NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);
}





void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/* 第一步：初始化需要连接到EXTI线的GPIO */
	
	RCC_AHB1PeriphClockCmd(KEY1_INT_GPIO_CLK|KEY2_INT_GPIO_CLK ,ENABLE);    /*开启按键GPIO口的时钟*/
	
  GPIO_InitStructure.GPIO_Pin  = KEY1_INT_GPIO_PIN;    	 /* 选择按键1的引脚 */ 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;           /* 设置引脚为输入模式 */	    		
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;       /* 设置引脚不上拉也不下拉 */  
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);    /* 使用上面的结构体初始化按键 */	
	 
  GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;       /* 选择按键2的引脚 */  
  GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);    /* 其他配置与上面相同 */
	
	
	
	/* 第二步：初始化EXTI */
	
	/* 使能 SYSCFG 时钟,使用GPIO外部中断时必须使能SYSCFG时钟*/	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  	
  SYSCFG_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE,KEY1_INT_EXTI_PINSOURCE);    /* 连接 EXTI 中断源 到 key1 引脚 */	
  SYSCFG_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE,KEY2_INT_EXTI_PINSOURCE);    /* 连接 EXTI 中断源 到 key2 引脚 */	
	
	
  EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;        /* 选择 EXTI 中断源 */  
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;       /* 中断模式 */  
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    /* 下降沿触发 */  
  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;    /* 使能中断/事件线 */
  EXTI_Init(&EXTI_InitStructure);
	
	
  EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;    /* 选择 EXTI 中断源 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;    /* 上升沿触发 */  
	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	
	
	
	/* 第三步：配置NVIC */
	
	NVIC_Configuration();
	
	
	/* 第四步：编写中断服务函数 */
	
	
	
	
	
	
}


/*

 */
