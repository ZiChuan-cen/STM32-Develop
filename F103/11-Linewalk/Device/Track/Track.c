/**
  ******************************************************************************
  * @file    Track.c
  * @author  zichuan
  * @date    2023-08-01
  * @brief   四路循迹模块
  ******************************************************************************
  */
  
  
#include "Track.h"



/**
    * @brief  配置循迹模块的GPIO
    * @pin    SW1:PB3	SW2:PB4		SW3:PB5		SW4:PB6
    * @param  无
    * @retval 无
    */
void Track_GPIO_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(Track_X_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = Track_X1_PIN | Track_X2_PIN | Track_X3_PIN | Track_X4_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Track_X_PORT, &GPIO_InitStructure);	
	
}


/**
    * @brief  获取巡线状态
    * @param  无
    * @retval 无
    */
void GetLine(int *p_iX1, int *p_iX2, int *p_iX3, int *p_iX4)
{
	*p_iX1 = GPIO_ReadInputDataBit(Track_X_PORT, Track_X1_PIN);
	
	*p_iX2 = GPIO_ReadInputDataBit(Track_X_PORT, Track_X2_PIN);
	
	*p_iX3 = GPIO_ReadInputDataBit(Track_X_PORT, Track_X3_PIN);
	
	*p_iX4 = GPIO_ReadInputDataBit(Track_X_PORT, Track_X4_PIN);
	
}


void LineWalking(void)
{
	int LineX1 = 1, LineX2 = 1, LineX3 = 1, LineX4 = 1;
	
	GetLine(&LineX1, &LineX2, &LineX3, &LineX4);		//获取黑线检测状态
	
	
	
	
}








