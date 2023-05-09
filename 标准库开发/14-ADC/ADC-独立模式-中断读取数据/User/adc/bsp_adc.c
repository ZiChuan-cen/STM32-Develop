#include "bsp_adc.h"


static void Rheostat_ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK, ENABLE);    // ʹ�� GPIO ʱ��		
	// ���� IO
	GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	    
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;    //������������
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT, &GPIO_InitStructure);		
}

static void Rheostat_ADC_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;	
  
	RCC_APB2PeriphClockCmd(RHEOSTAT_ADC_CLK , ENABLE);    // ����ADCʱ��

  /*-------------------ADC Common �ṹ�� ���� ��ʼ��------------------------*/
  	
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                         // ����ADCģʽ  
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;                      // ʱ��Ϊfpclk 4��Ƶ  
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;          // ��ֹDMAֱ�ӷ���ģʽ  	
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;    // ����ʱ����  
  ADC_CommonInit(&ADC_CommonInitStructure);
	
	/*-----------------------------------------------------------------------*/
	
  /*-------------------ADC Init �ṹ�� ���� ��ʼ��--------------------------*/
	ADC_StructInit(&ADC_InitStructure);  
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                  // ADC �ֱ���  	
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                           // ��ֹɨ��ģʽ����ͨ���ɼ�����Ҫ  	
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                      // ����ת��  
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;    // ��ֹ�ⲿ���ش���
  // �ⲿ����ͨ����������ʹ�������������ֵ��㸳ֵ����
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;  	
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                  // �����Ҷ���  
  ADC_InitStructure.ADC_NbrOfConversion = 1;                              // ת��ͨ�� 1��                                    
  ADC_Init(RHEOSTAT_ADC, &ADC_InitStructure);
  /*-----------------------------------------------------------------------*/
	
  // ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ3��ʱ������
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL, 1, ADC_SampleTime_56Cycles);
	// ADC ת�����������жϣ����жϷ�������ж�ȡת��ֵ
	ADC_ITConfig(RHEOSTAT_ADC, ADC_IT_EOC, ENABLE);  
  ADC_Cmd(RHEOSTAT_ADC, ENABLE);    // ʹ��ADC  
  ADC_SoftwareStartConv(RHEOSTAT_ADC);    //��ʼadcת�����������
}


// �����ж����ȼ�
static void Rheostat_ADC_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
  NVIC_InitStructure.NVIC_IRQChannel = Rheostat_ADC_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
  NVIC_Init(&NVIC_InitStructure);
}


void Rheostat_Init(void)
{
	Rheostat_ADC_GPIO_Config();
	Rheostat_ADC_Mode_Config();
	Rheostat_ADC_NVIC_Config();
}












