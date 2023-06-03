#include "bsp_usart.h"


/**
 * @brief  配置嵌套向量中断控制器NVIC
 * @param  无
 * @retval 无
 */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                /* 嵌套向量中断控制器组选择 */
    NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;          /* 配置USART为中断源 */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;      /* 抢断优先级为1 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             /* 子优先级为1 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                /* 使能中断 */
    NVIC_Init(&NVIC_InitStructure);                                /* 初始化配置NVIC */
}

void Debug_USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* 第一步：初始化串口所需GPIO */
    RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK | DEBUG_USART_TX_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    /* GPIO初始化 */
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    /* 配置Tx引脚为复用功能  */
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN  ;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    /* 配置Rx引脚为复用功能 */
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_PIN;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

    /* GPIO具体复用为什么第二功能 */

    /* 连接 PXx 到 USARTx_Tx*/
    GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);
    /*  连接 PXx 到 USARTx__Rx*/
    GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);


    /* 第二步：配置串口初始化结构体 */

    RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);    /* 使能 USART 时钟 */

    /* 配置串DEBUG_USART 模式 */
    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;     /* 波特率设置：DEBUG_USART_BAUDRATE */
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    /* 字长(数据位+校验位)：8 */
    USART_InitStructure.USART_StopBits = USART_StopBits_1;         /* 停止位：1个停止位 */
    USART_InitStructure.USART_Parity = USART_Parity_No;            /* 校验位选择：不使用校验 */
    /* 硬件流控制：不使用硬件流 */
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   /* USART模式控制：同时使能接收和发送 */
    USART_Init(DEBUG_USART, &USART_InitStructure);                    /* 完成USART初始化配置 */


    /* 第三步：配置串口的接收中断 */
//  NVIC_Configuration();    /* 嵌套向量中断控制器NVIC配置 */
//  USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);    /* 使能串口接收中断 */


    /* 第四步：使能串口 */
    USART_Cmd(DEBUG_USART, ENABLE);    /* 使能串口 */


}


/*****************  发送一个字符 **********************/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* 发送一个字节数据到USART */
    USART_SendData(pUSARTx, ch);

    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


/*****************  发送字符串 **********************/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int k = 0;
    do
    {
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    }
    while (*(str + k) != '\0');

    /* 等待发送完成 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
    {}
}


///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口 */
    USART_SendData(DEBUG_USART, (uint8_t) ch);

    /* 等待发送完毕 */
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);

    return (ch);
}


///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
    /* 等待串口输入数据 */
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(DEBUG_USART);
}













