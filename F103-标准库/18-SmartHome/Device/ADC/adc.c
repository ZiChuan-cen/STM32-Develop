#include "adc.h"
#include "delay.h"
#include "stdlib.h"

void  Adc_Init(void)
{ 	 
	GPIO_InitTypeDef GPIO_InitStructure;
			// 1. RCC开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	// ADCCLK = 72MHz / 6 = 12MHz
	
	// 2. 配置GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 3. 将指定的GPIO端口接入规则组列表中
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);	// 把通道8填入序列1中，通道的采样周期是55.5个ADCCLK的周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_55Cycles5);
	// 4. 配置ADC
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;						// ADC模式（独立模式或双ADC模式）：独立模式						
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;					// ADC数据对齐：右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// ADC外部触发源选择：不使用外部源触发（这里使用软件触发）
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;					// ADC连续转换模式：单次转换
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;							// ADC扫描模式：非扫描
	ADC_InitStruct.ADC_NbrOfChannel = 2;								// 扫描模式下通道的数量
	ADC_Init(ADC1, &ADC_InitStruct);
	
	/*	中断和模拟看门狗在此配置	*/
	
	// 5. 开关控制
	ADC_Cmd(ADC1, ENABLE);
	
	// 6. 对ADC进行校准
	ADC_ResetCalibration(ADC1);								// 复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);		// 等待复位校准完成
	ADC_StartCalibration(ADC1);								// 开始校准
	while (ADC_GetCalibrationStatus(ADC1) == SET);			// 等待校准完成
}			  


u16 Get_ADC(uint8_t channel)
{
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_55Cycles5);
	// 1. 软件触发开启转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	// 2. 等待转换完成（获取标志位状态，等待EOC标志位置1）
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);		// 转换未完成则等待（55.5T + 12.5T = 68T，结果大概为5.6us）
	// 3. 读取ADC数据寄存器并返回
	return ADC_GetConversionValue(ADC1);	// 读取之后会自动清除EOC标志位
}




u16 Get_Value(uint8_t channel)
{
	int i;
	int sum=0;
	for(i=0;i<10;i++)sum+=Get_ADC(channel);
	return sum/10;


}






















