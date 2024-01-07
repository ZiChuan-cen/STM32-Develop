#include "usart.h"
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
    int handle; 

}; 

FILE __stdout;       

void _sys_exit(int x) 
{ 
    x = x; 
} 

int fputc(int ch, FILE *f)
{      
    while((USART3->SR&0X40)==0); 
    USART3->DR = (u8) ch;      
    return ch;
}
#endif 



uint8_t usart3Rxbuf[512]={0};
uint8_t usart3Rxlen;

//usart3 初始化
void usart3_Init(u32 bound)
{
    
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	// 外设使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	//USART_DeInit(USART3);  //复位串口2 -> 可以没有
	
	// 初始化 串口对应IO口  TX-PA2  RX-PA3
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_11;
  GPIO_Init(GPIOB,&GPIO_InitStrue);
	
	// 初始化 串口模式状态
	USART_InitStrue.USART_BaudRate=bound; // 波特率
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; // 硬件流控制
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; // 发送 接收 模式都使用
	USART_InitStrue.USART_Parity=USART_Parity_No; // 没有奇偶校验
	USART_InitStrue.USART_StopBits=USART_StopBits_1; // 一位停止位
	USART_InitStrue.USART_WordLength=USART_WordLength_8b; // 每次发送数据宽度为8位
	USART_Init(USART3,&USART_InitStrue);
	
	USART_Cmd(USART3,ENABLE);//使能串口
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//开启接收中断
	
	// 初始化 中断优先级
	NVIC_InitStrue.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
}



//串口3发送一个字符
int Usart3Send(int ch)
{   
    USART_SendData(USART3,ch);
    while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);//循环发送,直到发送完毕   
          
    return ch;
}
 
//串口3发送字符串
void USART3_SendStr(char *Str,int lenth)
{
    int i = 0;
    for(i = 0; i < lenth; i++)
    {
        Usart3Send(Str[i]);
    }
    
}
void USART3_SendString(char *Str)
{
    while(*Str!='\0')
		{
				Usart3Send(*Str++);
		}
}



uint8_t usart1Rxbuf[256]={0};
uint8_t usart1Rxlen;

//usart1 初始化
void usart1_Init(u32 bound)
{
    
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	// 外设使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//USART_DeInit(USART1);  //复位串口2 -> 可以没有
	
	// 初始化 串口对应IO口  TX-PA9  RX-PA10
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
  GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	// 初始化 串口模式状态
	USART_InitStrue.USART_BaudRate=bound; // 波特率
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; // 硬件流控制
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; // 发送 接收 模式都使用
	USART_InitStrue.USART_Parity=USART_Parity_No; // 没有奇偶校验
	USART_InitStrue.USART_StopBits=USART_StopBits_1; // 一位停止位
	USART_InitStrue.USART_WordLength=USART_WordLength_8b; // 每次发送数据宽度为8位
	USART_Init(USART1,&USART_InitStrue);
	
	USART_Cmd(USART1,ENABLE);//使能串口
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启接收中断
	
	// 初始化 中断优先级
	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
}



//串口3发送一个字符
int Usart1Send(int ch)
{   
    USART_SendData(USART1,ch);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//循环发送,直到发送完毕   
          
    return ch;
}
 
//串口3发送字符串
void USART1_SendStr(char *Str,int lenth)
{
    int i = 0;
    for(i = 0; i < lenth; i++)
    {
        Usart1Send(Str[i]);
    }
    
}
void USART1_SendString(char *Str)
{
    while(*Str!='\0')
		{
				Usart1Send(*Str++);
		}
}

