#include "ESP.h"
#include <stdio.h>
#include <string.h>


char RECS[250];
unsigned char i;




void ESP_GPIO_Init(void)
{
    /*********************************** 构造结构体 ***********************************/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef   USART_InitStructure;
    NVIC_InitTypeDef    NVIC_InitStructure;


    /*********************************** 配置GPIO ***********************************/
    RCC_APB2PeriphClockCmd(USART3_GPIO_CLK, ENABLE);

    //PB10  USART3_TX
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;    //复用推挽输出
    GPIO_InitStructure.GPIO_Pin   = USART3_TX_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART3_TX_PORT, &GPIO_InitStructure);     //初始化寄存器

    //PB11  USART3_RX
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;  //下拉输入
    GPIO_InitStructure.GPIO_Pin   = USART3_RX_Pin;
    GPIO_Init(USART3_RX_PORT, &GPIO_InitStructure);     //初始化寄存器

    /*********************************** 配置串口 ***********************************/
    RCC_APB1PeriphClockCmd(USART3_CLK, ENABLE);

    USART_InitStructure.USART_BaudRate  =   115200;
    USART_InitStructure.USART_HardwareFlowControl   =   DISABLE;
    USART_InitStructure.USART_Mode  =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity    =   USART_Parity_No;
    USART_InitStructure.USART_StopBits  =   USART_StopBits_1;
    USART_InitStructure.USART_WordLength    =   USART_WordLength_8b;

    USART_Init(USART3, &USART_InitStructure);   //初始化寄存器
    USART_Cmd(USART3, ENABLE);  //使能串口

    /*********************************** 配置NVIC ***********************************/
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

}



char *ESP_GetString(void)//串口获取字符串
{
    return RECS;
}
void ESP_SendString(char *str)//串口发送字符串
{
    uint8_t stri = 0;
    while (str[stri] != '\0')
        USART_SendData(USART3, str[stri++]);
}
//void USART3_IRQHandler()//串口中断并将接收数据存放在RECS数组中
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





//printf重定向
int fputc(int c, FILE *stream)
{
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == 0) {}
    USART_SendData(USART3, c);
    return c;
}



