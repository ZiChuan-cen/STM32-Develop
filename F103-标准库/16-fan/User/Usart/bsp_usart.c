/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @author  zichuan
  * @date    2023-06-08
  * @brief   ���ô���
  ******************************************************************************
  */

#include "bsp_usart.h"
#include <stdio.h>
#include <stdarg.h>


uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

/**
    * @brief  ����USART1
	* @pin	  UART1_TX:PA9	UART1_RX:PA10
    * @param  ��
    * @retval ��
    */
void Usart1_Config(void)
{	
/*********************************����GPIO*************************************/	
	RCC_APB2PeriphClockCmd(USART1_GPIO_CLK, ENABLE);	
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	//PA9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Pin  = USART1_TX_Pin;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);//��ʼ���Ĵ���	
	//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin  = USART1_RX_Pin;	
	GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);  //��ʼ���Ĵ���
	
/*********************************���ô���*************************************/	
	RCC_APB2PeriphClockCmd(USART1_CLK, ENABLE);  //��������ʱ��	
	USART_InitTypeDef USART_InitStructure = {0};
	
	USART_InitStructure.USART_BaudRate = 115200;  //������
	USART_InitStructure.USART_HardwareFlowControl = DISABLE;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	USART_InitStructure.USART_Parity = USART_Parity_No;  //��ʹ����żУ��
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1, &USART_InitStructure); //��ʼ���Ĵ���	
	USART_Cmd(USART1, ENABLE); //ʹ�ܴ���	
}



void Usart2_Config(void)
{
	/********************************* ���ýṹ�� *************************************/
    GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef   USART_InitStructure = {0};
    NVIC_InitTypeDef    NVIC_InitStructure;

    /********************************* ����GPIO *************************************/
    RCC_APB2PeriphClockCmd(USART2_GPIO_CLK, ENABLE);
    //PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //�����������
    GPIO_InitStructure.GPIO_Pin  = USART2_TX_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_TX_PORT, &GPIO_InitStructure);
    //PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //��������
    GPIO_InitStructure.GPIO_Pin  = USART2_RX_Pin;
    GPIO_Init(USART2_RX_PORT, &GPIO_InitStructure);

    /********************************* ���ô��� *************************************/
    RCC_APB1PeriphClockCmd(USART2_CLK, ENABLE);  //��������ʱ��

    USART_InitStructure.USART_BaudRate = 9600;  //������
    USART_InitStructure.USART_HardwareFlowControl = DISABLE;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;  //��ʹ����żУ��
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    USART_Init(USART2, &USART_InitStructure);       //��ʼ���Ĵ���
    USART_Cmd(USART2, ENABLE);              //ʹ�ܴ���2

    /********************************* �����ж� *************************************/
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);      //���������ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

    NVIC_Init(&NVIC_InitStructure);

}



void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART2, Byte);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}

void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		Serial_RxData = USART_ReceiveData(USART2);
		Serial_SendByte(Serial_RxData);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}



//printf�ض���
int fputc(int c, FILE *stream)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == 0) {}
    USART_SendData(USART1, c);
    return c;
}





