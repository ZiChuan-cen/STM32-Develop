#include "adc.h"
#include "delay.h"
#include "stdlib.h"

void  Adc_Init(void)
{ 	 
	GPIO_InitTypeDef GPIO_InitStructure;
			// 1. RCC����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	// ADCCLK = 72MHz / 6 = 12MHz
	
	// 2. ����GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 3. ��ָ����GPIO�˿ڽ���������б���
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);	// ��ͨ��8��������1�У�ͨ���Ĳ���������55.5��ADCCLK������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_55Cycles5);
	// 4. ����ADC
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;						// ADCģʽ������ģʽ��˫ADCģʽ��������ģʽ						
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;					// ADC���ݶ��룺�Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// ADC�ⲿ����Դѡ�񣺲�ʹ���ⲿԴ����������ʹ�����������
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;					// ADC����ת��ģʽ������ת��
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;							// ADCɨ��ģʽ����ɨ��
	ADC_InitStruct.ADC_NbrOfChannel = 2;								// ɨ��ģʽ��ͨ��������
	ADC_Init(ADC1, &ADC_InitStruct);
	
	/*	�жϺ�ģ�⿴�Ź��ڴ�����	*/
	
	// 5. ���ؿ���
	ADC_Cmd(ADC1, ENABLE);
	
	// 6. ��ADC����У׼
	ADC_ResetCalibration(ADC1);								// ��λУ׼
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);		// �ȴ���λУ׼���
	ADC_StartCalibration(ADC1);								// ��ʼУ׼
	while (ADC_GetCalibrationStatus(ADC1) == SET);			// �ȴ�У׼���
}			  


u16 Get_ADC(uint8_t channel)
{
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_55Cycles5);
	// 1. �����������ת��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	// 2. �ȴ�ת����ɣ���ȡ��־λ״̬���ȴ�EOC��־λ��1��
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);		// ת��δ�����ȴ���55.5T + 12.5T = 68T��������Ϊ5.6us��
	// 3. ��ȡADC���ݼĴ���������
	return ADC_GetConversionValue(ADC1);	// ��ȡ֮����Զ����EOC��־λ
}




u16 Get_Value(uint8_t channel)
{
	int i;
	int sum=0;
	for(i=0;i<10;i++)sum+=Get_ADC(channel);
	return sum/10;


}






















