/**
  ******************************************************************************
  * @file    BH1750.c
  * @author  zichuan
  * @date    2023-06-08
  * @brief   ����ǿ�ȴ�����,IIC
  ******************************************************************************
  */


#include "BH1750.h"
#include "delay.h"

uchar    BUF[8];               //�������ݻ�����
int   mcy;          //��λ��־


/**
    * @brief  ��ʼ�ź�
    * @param  ��
    * @retval ��
    */
void BH1750_Start()
{
    SDA_High;                           //����������
    SCL_High;                           //����ʱ����
    Delay_us(5);                        //��ʱ
    GPIO_ResetBits(bh1750_PORT, sda);                    //�����½���
    Delay_us(5);                        //��ʱ
    GPIO_ResetBits(bh1750_PORT, scl);                    //����ʱ����
}


/**
    * @brief  ֹͣ�ź�
    * @param  ��
    * @retval ��
    */
void BH1750_Stop()
{
    SDA_Low;                        //����������
    SCL_High;                       //����ʱ����
    Delay_us(5);                    //��ʱ
    GPIO_SetBits(bh1750_PORT, sda);                    //����������
    Delay_us(5);                    //��ʱ
}



/**
    * @brief  ����Ӧ���ź�
    * @param  ack (0:ACK 1:NAK)
    * @retval ��
    */
void BH1750_SendACK(int ack)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = sda;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);

    if (ack == 1)               //дӦ���ź�
        SDA_High;                   //����������
    else if (ack == 0)
        SDA_Low;                    //����������
    else
        return;
    SCL_High;                       //����ʱ����
    Delay_us(5);                //��ʱ
    SCL_Low;                        //����ʱ����
    Delay_us(5);                //��ʱ
}


/**
    * @brief  ����Ӧ���ź�
    * @param  ��
    * @retval ��
    */
int BH1750_RecvACK()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* ����һ��Ҫ������������������ܶ������� */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = sda;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);

    SCL_High;                           //����ʱ����
    Delay_us(5);                 //��ʱ
    if (GPIO_ReadInputDataBit(bh1750_PORT, sda) == 1) //��Ӧ���ź�
        mcy = 1 ;
    else
        mcy = 0 ;
    SCL_Low;                            //����ʱ����
    Delay_us(5);                 //��ʱ
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);
    return mcy;
}




/**
    * @brief  ��IIC���߷���һ���ֽ�����
    * @param  ��
    * @retval ��
    */
void BH1750_SendByte(uchar dat)
{
    uchar i;
    for (i = 0; i < 8; i++)     //8λ������
    {
        if (0X80 & dat)
            GPIO_SetBits(bh1750_PORT, sda);
        else
            GPIO_ResetBits(bh1750_PORT, sda);
        dat <<= 1;
        SCL_High;               //����ʱ����
        Delay_us(5);         //��ʱ
        SCL_Low;                //����ʱ����
        Delay_us(5);         //��ʱ
    }
    BH1750_RecvACK();           //����Ӧ���ź�
}

/**
    * @brief  ��IIC���߽���һ���ֽ�����
    * @param  ��
    * @retval ��
    */
uchar BH1750_RecvByte()
{
    uchar i;
    uchar dat = 0;              //dat�Ǵ�Ž��յ���һ���ֽڵ�����
    uchar bit;

    GPIO_InitTypeDef GPIO_InitStruct;

    /* ����һ��Ҫ������������������ܶ������� */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = sda;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);

    GPIO_SetBits(bh1750_PORT, sda);         //ʹ���ڲ�����,׼����ȡ����,
    for (i = 0; i < 8; i++)     //8λ������
    {
        dat <<= 1;
        SCL_High;             //����ʱ����
        Delay_us(5);             //��ʱ
        //��ȡSDA���ŵĵ�ƽ������Ǹߵ�ƽ�����Ǵ��䡰1��
        if (SET == GPIO_ReadInputDataBit(bh1750_PORT, sda))
            bit = 0X01;
        else
            bit = 0x00;
        dat |= bit;             //������
        SCL_Low;              //����ʱ����
        Delay_us(5);            //��ʱ
    }
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);
    return dat;
}

/**
    * @brief  д��ָ��
    * @param  REG_Address����Ҫд���ָ��
    * @retval ��
    */
void BH1750_Write_Com(uchar REG_Address)
{
    BH1750_Start();                  //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ
//  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ
    BH1750_Stop();                   //����ֹͣ�ź�
}


/**
    * @brief  ��ʼ��BH1750��������Ҫ��ο������ֲ�����޸�
    * @param  ��
    * @retval ��
    */
void BH1750_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /*����GPIOB������ʱ��*/
    RCC_APB2PeriphClockCmd(BH1750_CLK, ENABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = sda | scl ;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);

    BH1750_Write_Com(0x01);
    Delay_ms(180);            //��ʱ180ms
}


/**
    * @brief  ��ȡָ��/����
    * @param  ��
    * @retval ��
    */
void BH1750_Read_Com(void)
{
    uchar i;
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress + 1);       //�����豸��ַ+���ź�

    /* ֻ��Ҫ��ȡ2���ֽھ��У�����ĺϳ�����Ҳ��ֻ����BUF��ǰ2���ֽ�
       3���ֽڴ��Ҳ�а� */
    for (i = 0; i < 2; i++)                  //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 2)
        {
            BH1750_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
            BH1750_SendACK(0);                //��ӦACK
        }
    }
    BH1750_Stop();                          //ֹͣ�ź�
    Delay_ms(5);
}

/**
    * @brief  ��ȡ���ն�
    * @param  ��
* @retval temp2:����������        temp2:
    */
float BH1750_Read_Value(void)
{
    int dis_data;                       //����
    float temp2;
    BH1750_Write_Com(0x01);   // power on

    /* ��1lx�ֱ��ʿ�ʼ����������ʱ��ͨ��Ϊ120ms���������Զ�����Ϊ�ϵ�ģʽ */
    BH1750_Write_Com(0x10);
    Delay_ms(180);            //��ʱ180ms
    BH1750_Read_Com();       //�����������ݣ��洢��BUF��
    dis_data = BUF[0];
    dis_data = (dis_data << 8) + BUF[1]; //�ϳ�����
    temp2 = dis_data / 1.2;
//    temp2 = 10 * dis_data / 1.2;
//    temp2 = (int)temp2 % 10;
    return temp2;
}



