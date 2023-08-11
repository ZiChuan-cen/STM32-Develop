#include "ESP.h"
#include <stdio.h>
#include <string.h>


char RECS[250];
unsigned char i;




void ESP_GPIO_Init(void)
{
    /*********************************** ����ṹ�� ***********************************/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef   USART_InitStructure;
    NVIC_InitTypeDef    NVIC_InitStructure;


    /*********************************** ����GPIO ***********************************/
    RCC_APB2PeriphClockCmd(USART3_GPIO_CLK, ENABLE);

    //PB10  USART3_TX
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;    //�����������
    GPIO_InitStructure.GPIO_Pin   = USART3_TX_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART3_TX_PORT, &GPIO_InitStructure);     //��ʼ���Ĵ���

    //PB11  USART3_RX
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;  //��������
    GPIO_InitStructure.GPIO_Pin   = USART3_RX_Pin;
    GPIO_Init(USART3_RX_PORT, &GPIO_InitStructure);     //��ʼ���Ĵ���

    /*********************************** ���ô��� ***********************************/
    RCC_APB1PeriphClockCmd(USART3_CLK, ENABLE);

    USART_InitStructure.USART_BaudRate  =   115200;
    USART_InitStructure.USART_HardwareFlowControl   =   DISABLE;
    USART_InitStructure.USART_Mode  =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity    =   USART_Parity_No;
    USART_InitStructure.USART_StopBits  =   USART_StopBits_1;
    USART_InitStructure.USART_WordLength    =   USART_WordLength_8b;

    USART_Init(USART3, &USART_InitStructure);   //��ʼ���Ĵ���
    USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���

    /*********************************** ����NVIC ***********************************/
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

}



char *ESP_GetString(void)//���ڻ�ȡ�ַ���
{
    return RECS;
}
void ESP_SendString(char *str)//���ڷ����ַ���
{
    uint8_t stri = 0;
    while (str[stri] != '\0')
        USART_SendData(USART3, str[stri++]);
}
//void USART3_IRQHandler()//�����жϲ����������ݴ����RECS������
//{
//  if(USART_GetITStatus(USART3,USART_IT_RXNE))
//  {
//      RECS[i++]=USART_ReceiveData(USART3);
//      if((RECS[i-2]=='\r')|(RECS[i-1]=='\n'))
//      {
//          RECS[i-2]='\0';
//          i = 0;
//          CommandAnalyse();
//      }
//  }
//}





//printf�ض���
int fputc(int c, FILE *stream)
{
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == 0) {}
    USART_SendData(USART3, c);
    return c;
}



