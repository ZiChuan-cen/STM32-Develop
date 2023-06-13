#include "bsp_exti.h"


static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����NVICΪ���ȼ���1 */
	/* ��ʾ NVIC_PriorityGroupConfig() ����������ֻ��Ҫ����һ�����������ȼ�����*/
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  
  
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;      /* �����ж�Դ������1 */  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    /* ������ռ���ȼ���1 */  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;           /* ���������ȼ���1 */  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              /* ʹ���ж�ͨ�� */
  NVIC_Init(&NVIC_InitStructure);
  
  /* �����ж�Դ������2������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);
}





void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/* ��һ������ʼ����Ҫ���ӵ�EXTI�ߵ�GPIO */
	
	RCC_AHB1PeriphClockCmd(KEY1_INT_GPIO_CLK|KEY2_INT_GPIO_CLK ,ENABLE);    /*��������GPIO�ڵ�ʱ��*/
	
  GPIO_InitStructure.GPIO_Pin  = KEY1_INT_GPIO_PIN;    	 /* ѡ�񰴼�1������ */ 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;           /* ��������Ϊ����ģʽ */	    		
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;       /* �������Ų�����Ҳ������ */  
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);    /* ʹ������Ľṹ���ʼ������ */	
	 
  GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;       /* ѡ�񰴼�2������ */  
  GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);    /* ����������������ͬ */
	
	
	
	/* �ڶ�������ʼ��EXTI */
	
	/* ʹ�� SYSCFG ʱ��,ʹ��GPIO�ⲿ�ж�ʱ����ʹ��SYSCFGʱ��*/	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  	
  SYSCFG_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE,KEY1_INT_EXTI_PINSOURCE);    /* ���� EXTI �ж�Դ �� key1 ���� */	
  SYSCFG_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE,KEY2_INT_EXTI_PINSOURCE);    /* ���� EXTI �ж�Դ �� key2 ���� */	
	
	
  EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;        /* ѡ�� EXTI �ж�Դ */  
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;       /* �ж�ģʽ */  
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    /* �½��ش��� */  
  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;    /* ʹ���ж�/�¼��� */
  EXTI_Init(&EXTI_InitStructure);
	
	
  EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;    /* ѡ�� EXTI �ж�Դ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;    /* �����ش��� */  
	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	
	
	
	/* ������������NVIC */
	
	NVIC_Configuration();
	
	
	/* ���Ĳ�����д�жϷ����� */
	
	
	
	
	
	
}


/*

 */
