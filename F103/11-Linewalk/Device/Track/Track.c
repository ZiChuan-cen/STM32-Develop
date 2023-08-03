/**
  ******************************************************************************
  * @file    Track.c
  * @author  zichuan
  * @date    2023-08-01
  * @brief   ��·ѭ��ģ��
  ******************************************************************************
  */


#include "Track.h"
#include "stdio.h"
#include "delay.h"



/**
    * @brief  ����ѭ��ģ���GPIO
    * @pin    SW1:PB3   SW2:PB4     SW3:PB5     SW4:PB6
    * @param  ��
    * @retval ��
    */
void Track_GPIO_Init(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(Track_X_RCC, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //��������
    GPIO_InitStructure.GPIO_Pin = Track_X1_PIN | Track_X2_PIN | Track_X3_PIN | Track_X4_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(Track_X_PORT, &GPIO_InitStructure);

}


/**
    * @brief  ��ȡѲ��״̬
    * @param  ��
    * @retval ��
    */
void GetLine(int *p_iX1, int *p_iX2, int *p_iX3, int *p_iX4)
{
    *p_iX1 = GPIO_ReadInputDataBit(Track_X_PORT, Track_X1_PIN);

    *p_iX2 = GPIO_ReadInputDataBit(Track_X_PORT, Track_X2_PIN);

    *p_iX3 = GPIO_ReadInputDataBit(Track_X_PORT, Track_X3_PIN);

    *p_iX4 = GPIO_ReadInputDataBit(Track_X_PORT, Track_X4_PIN);

}


int LineWalking(void)
{
    int LineX1 = 1, LineX2 = 1, LineX3 = 1, LineX4 = 1;

    GetLine(&LineX1, &LineX2, &LineX3, &LineX4);        //��ȡ���߼��״̬
	
    if ((LineX1 == LOW || LineX3 == LOW) && LineX4 == LOW)       //����ǣ��Ҵ��䣻LOW��ʾ��⵽����
    {
        return 1;       //���ݸ�����������
        Delay_ms(80);
    }
    else if (LineX2 == LOW && (LineX1 == LOW || LineX3 == LOW))      //����ǣ������
    {
        return 2;
        Delay_ms(80);
    }
	else if (LineX2 == LOW)			//���������
	{
		return 3;
		Delay_ms(80);
	}
	else if (LineX4 == LOW)			//���������
	{
		return 4;
		Delay_ms(80);
	}
	else if (LineX1 == LOW && LineX3 == HIGH)		//΢������ת
	{
		return 5;
		Delay_ms(80);
	}
	else if (LineX1 == HIGH && LineX3 == LOW)		//΢������ת
	{
		return 6;
		Delay_ms(80);
	}
	else if (LineX1 == LOW && LineX3 == LOW)		//����ǰ��
	{
		return 7;
	}
	
	return 0;

}





















