/**
  ******************************************************************************
  * @file    dht11.c
  * @author  fire
  * @date    2023-06-08
  * @brief   温湿度传感器配置
  ******************************************************************************
  * @attention
  *
  * 平台:野火  STM32 f103 RCt6 开发板
  *
  ******************************************************************************
  */

#include "dht11.h"
#include "delay.h"



/**
    * @brief  配置GPIO DHT11输入输出模式转换
    * @param  无
    * @retval 无
    */
void Change_Dht11_Mode(DHT11Mode_TypeDef mode)
{
    RCC_APB2PeriphClockCmd(DHT11_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin   = DHT11_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    if (mode == DHT11Mode_IN)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == DHT11Mode_OUT)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    }

    GPIO_Init(DHT11_IO, &GPIO_InitStructure);
}


/**
    * @brief  主机读取、校验 DHT11 数据
    * @param  无
    * @retval data
    */
u8 Dht11_ReadData(DHT11_Data_TypeDef *data)
{
    u8 Data[5] = {0};

    /************************************起始信号--输出*******************************************************/
    Change_Dht11_Mode(DHT11Mode_OUT);
    DHT11_HIGHT();
    DHT11_LOW();
    Delay_ms(20);
    DHT11_HIGHT();  //拉高等待
    Delay_us(30);
    /************************************应答信号--输入*******************************************************/
    Change_Dht11_Mode(DHT11Mode_IN);
    while (DHT11_ReadPin() == Bit_SET) //等待变为低电平
    {}
    while (DHT11_ReadPin() == Bit_RESET) //等待变为高电平
    {}

    /**************************************数据的发送**********************************************************/
    for (u8 i = 0; i < 40; i++)
    {
        while (DHT11_ReadPin() == Bit_SET) //拉低54us
        {}
        while (DHT11_ReadPin() == Bit_RESET) //拉高等待判断
        {}

        /***********************************判断数据‘1’数据‘0’**************************************************/

        Delay_us(40);
        if (DHT11_ReadPin() == Bit_SET) //如果为高电平，1
        {
            Data[i / 8] |= (1 << (7 - i % 8));
        }
        else//0
        {
            Data[i / 8] &= ~(1 << (7 - i % 8));
        }
    }

    /********************************************校验********************************************************/
    if (Data[4] == Data[0] + Data[1] + Data[2] + Data[3])
    {
        data->Hum = Data[0];
        data->Tem = Data[2];
        return 1;
    }
    else
    {
        return 0;
    }
}



/**
    * @brief  检测DHT11的响应信号
    * @param  无
    * @retval 检测到回应-->返回1，否则0，data error
    */
u8 DHT11_Check(void)
{
    u8 retry = 0;
    Change_Dht11_Mode(DHT11Mode_IN);            //设置为输入模式

    while (!GPIO_ReadInputDataBit(DHT11_IO, DHT11_Pin) && retry < 100) //DHT11会拉低40~50us
    {
        retry++;
        Delay_us(1);
    }
    if (retry >= 100)   //超时未响应/未收到开始信号，退出检测
    {
        //printf("1 data error \r\n");
        return 0;
    }
    else
    {
        retry = 0;
    }
    while (GPIO_ReadInputDataBit(DHT11_IO, DHT11_Pin) && retry < 100) //DHT11拉低后会再次拉高40~50us
    {
        retry++;
        Delay_us(1);
    }
    if (retry >= 100)   //超时，DHT11工作出错，退出检测
    {
        //printf("2 data error \r\n");
        return 0;
    }
    return 1;                   //设备正常响应，可以正常工作
}


