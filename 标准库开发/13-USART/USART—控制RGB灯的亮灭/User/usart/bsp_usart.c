#include "bsp_usart.h"


/**
 * @brief  ����Ƕ�������жϿ�����NVIC
 * @param  ��
 * @retval ��
 */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                /* Ƕ�������жϿ�������ѡ�� */
    NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;          /* ����USARTΪ�ж�Դ */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;      /* �������ȼ�Ϊ1 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;             /* �����ȼ�Ϊ1 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                /* ʹ���ж� */
    NVIC_Init(&NVIC_InitStructure);                                /* ��ʼ������NVIC */
}

void Debug_USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* ��һ������ʼ����������GPIO */
    RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK | DEBUG_USART_TX_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    /* GPIO��ʼ�� */
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    /* ����Tx����Ϊ���ù���  */
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN  ;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    /* ����Rx����Ϊ���ù��� */
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_PIN;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

    /* GPIO���帴��Ϊʲô�ڶ����� */

    /* ���� PXx �� USARTx_Tx*/
    GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);
    /*  ���� PXx �� USARTx__Rx*/
    GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);


    /* �ڶ��������ô��ڳ�ʼ���ṹ�� */

    RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);    /* ʹ�� USART ʱ�� */

    /* ���ô�DEBUG_USART ģʽ */
    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;     /* ���������ã�DEBUG_USART_BAUDRATE */
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;    /* �ֳ�(����λ+У��λ)��8 */
    USART_InitStructure.USART_StopBits = USART_StopBits_1;         /* ֹͣλ��1��ֹͣλ */
    USART_InitStructure.USART_Parity = USART_Parity_No;            /* У��λѡ�񣺲�ʹ��У�� */
    /* Ӳ�������ƣ���ʹ��Ӳ���� */
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   /* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
    USART_Init(DEBUG_USART, &USART_InitStructure);                    /* ���USART��ʼ������ */


    /* �����������ô��ڵĽ����ж� */
//  NVIC_Configuration();    /* Ƕ�������жϿ�����NVIC���� */
//  USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);    /* ʹ�ܴ��ڽ����ж� */


    /* ���Ĳ���ʹ�ܴ��� */
    USART_Cmd(DEBUG_USART, ENABLE);    /* ʹ�ܴ��� */


}


/*****************  ����һ���ַ� **********************/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* ����һ���ֽ����ݵ�USART */
    USART_SendData(pUSARTx, ch);

    /* �ȴ��������ݼĴ���Ϊ�� */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


/*****************  �����ַ��� **********************/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int k = 0;
    do
    {
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    }
    while (*(str + k) != '\0');

    /* �ȴ�������� */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
    {}
}


///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
    /* ����һ���ֽ����ݵ����� */
    USART_SendData(DEBUG_USART, (uint8_t) ch);

    /* �ȴ�������� */
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);

    return (ch);
}


///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
    /* �ȴ������������� */
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(DEBUG_USART);
}













