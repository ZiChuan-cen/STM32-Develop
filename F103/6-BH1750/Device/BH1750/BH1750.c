/**
  ******************************************************************************
  * @file    BH1750.c
  * @author  zichuan
  * @date    2023-06-08
  * @brief   光照强度传感器,IIC
  ******************************************************************************
  */


#include "BH1750.h"
#include "delay.h"

uchar    BUF[8];               //接收数据缓存区
int   mcy;          //进位标志


/**
    * @brief  开始信号
    * @param  无
    * @retval 无
    */
void BH1750_Start()
{
    SDA_High;                           //拉高数据线
    SCL_High;                           //拉高时钟线
    Delay_us(5);                        //延时
    GPIO_ResetBits(bh1750_PORT, sda);                    //产生下降沿
    Delay_us(5);                        //延时
    GPIO_ResetBits(bh1750_PORT, scl);                    //拉低时钟线
}


/**
    * @brief  停止信号
    * @param  无
    * @retval 无
    */
void BH1750_Stop()
{
    SDA_Low;                        //拉低数据线
    SCL_High;                       //拉高时钟线
    Delay_us(5);                    //延时
    GPIO_SetBits(bh1750_PORT, sda);                    //产生上升沿
    Delay_us(5);                    //延时
}



/**
    * @brief  发送应答信号
    * @param  ack (0:ACK 1:NAK)
    * @retval 无
    */
void BH1750_SendACK(int ack)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = sda;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);

    if (ack == 1)               //写应答信号
        SDA_High;                   //拉高数据线
    else if (ack == 0)
        SDA_Low;                    //拉低数据线
    else
        return;
    SCL_High;                       //拉高时钟线
    Delay_us(5);                //延时
    SCL_Low;                        //拉低时钟线
    Delay_us(5);                //延时
}


/**
    * @brief  接收应答信号
    * @param  无
    * @retval 无
    */
int BH1750_RecvACK()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* 这里一定要设成输入上拉，否则不能读出数据 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = sda;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);

    SCL_High;                           //拉高时钟线
    Delay_us(5);                 //延时
    if (GPIO_ReadInputDataBit(bh1750_PORT, sda) == 1) //读应答信号
        mcy = 1 ;
    else
        mcy = 0 ;
    SCL_Low;                            //拉低时钟线
    Delay_us(5);                 //延时
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);
    return mcy;
}




/**
    * @brief  向IIC总线发送一个字节数据
    * @param  无
    * @retval 无
    */
void BH1750_SendByte(uchar dat)
{
    uchar i;
    for (i = 0; i < 8; i++)     //8位计数器
    {
        if (0X80 & dat)
            GPIO_SetBits(bh1750_PORT, sda);
        else
            GPIO_ResetBits(bh1750_PORT, sda);
        dat <<= 1;
        SCL_High;               //拉高时钟线
        Delay_us(5);         //延时
        SCL_Low;                //拉低时钟线
        Delay_us(5);         //延时
    }
    BH1750_RecvACK();           //接收应答信号
}

/**
    * @brief  在IIC总线接收一个字节数据
    * @param  无
    * @retval 无
    */
uchar BH1750_RecvByte()
{
    uchar i;
    uchar dat = 0;              //dat是存放接收到的一个字节的数据
    uchar bit;

    GPIO_InitTypeDef GPIO_InitStruct;

    /* 这里一定要设成输入上拉，否则不能读出数据 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = sda;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);

    GPIO_SetBits(bh1750_PORT, sda);         //使能内部上拉,准备读取数据,
    for (i = 0; i < 8; i++)     //8位计数器
    {
        dat <<= 1;
        SCL_High;             //拉高时钟线
        Delay_us(5);             //延时
        //读取SDA引脚的电平，如果是高电平，就是传输“1”
        if (SET == GPIO_ReadInputDataBit(bh1750_PORT, sda))
            bit = 0X01;
        else
            bit = 0x00;
        dat |= bit;             //读数据
        SCL_Low;              //拉低时钟线
        Delay_us(5);            //延时
    }
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);
    return dat;
}

/**
    * @brief  写入指令
    * @param  REG_Address：是要写入的指令
    * @retval 无
    */
void BH1750_Write_Com(uchar REG_Address)
{
    BH1750_Start();                  //起始信号
    BH1750_SendByte(SlaveAddress);   //发送设备地址+写信号
    BH1750_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页
//  BH1750_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页
    BH1750_Stop();                   //发送停止信号
}


/**
    * @brief  初始化BH1750，根据需要请参考数据手册进行修改
    * @param  无
    * @retval 无
    */
void BH1750_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /*开启GPIOB的外设时钟*/
    RCC_APB2PeriphClockCmd(BH1750_CLK, ENABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = sda | scl ;
    GPIO_Init(bh1750_PORT, &GPIO_InitStruct);

    BH1750_Write_Com(0x01);
    Delay_ms(180);            //延时180ms
}


/**
    * @brief  读取指令/数据
    * @param  无
    * @retval 无
    */
void BH1750_Read_Com(void)
{
    uchar i;
    BH1750_Start();                          //起始信号
    BH1750_SendByte(SlaveAddress + 1);       //发送设备地址+读信号

    /* 只需要读取2个字节就行，后面的合成数据也是只用了BUF的前2个字节
       3个字节大概也行吧 */
    for (i = 0; i < 2; i++)                  //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 2)
        {
            BH1750_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
            BH1750_SendACK(0);                //回应ACK
        }
    }
    BH1750_Stop();                          //停止信号
    Delay_ms(5);
}

/**
    * @brief  获取光照度
    * @param  无
* @retval temp2:处理后的数据        temp2:
    */
float BH1750_Read_Value(void)
{
    int dis_data;                       //变量
    float temp2;
    BH1750_Write_Com(0x01);   // power on

    /* 以1lx分辨率开始测量，测量时间通常为120ms，测量后自动设置为断电模式 */
    BH1750_Write_Com(0x10);
    Delay_ms(180);            //延时180ms
    BH1750_Read_Com();       //连续读出数据，存储在BUF中
    dis_data = BUF[0];
    dis_data = (dis_data << 8) + BUF[1]; //合成数据
    temp2 = dis_data / 1.2;
//    temp2 = 10 * dis_data / 1.2;
//    temp2 = (int)temp2 % 10;
    return temp2;
}



