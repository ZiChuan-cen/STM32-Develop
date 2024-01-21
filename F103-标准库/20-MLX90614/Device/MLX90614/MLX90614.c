#include "mlx90614.h"
#include "delay.h"
 
//MLX初始化函数
void MLX906_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIOB时钟
    //初始化引脚
    GPIO_InitTypeDef mlx906_gpio_init;
    mlx906_gpio_init.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
    mlx906_gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    mlx906_gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&mlx906_gpio_init);
    
    MLX906_SCL_H;//拉高引脚电平
    MLX906_SDA_H;
}
 
/*    IIC   时序    */
 
//起始信号
void MLX906_START_Sign(void)
{
    MLX906_SDA_OUT();//输出模式
    MLX906_SDA_H;
    MLX906_SCL_H;
    Delay_us(2);
    MLX906_SDA_L;
    Delay_us(2);
    MLX906_SCL_L;//钳住总线，准备开始数据传输
    Delay_us(1);
}
//停止信号
void MLX906_STOP_Sign(void)
{
    MLX906_SDA_OUT();//输出模式
    MLX906_SCL_L;
    MLX906_SDA_L;
    Delay_us(2);
    MLX906_SCL_H;
    MLX906_SDA_H;
    Delay_us(1);
}
uint8_t MLX906_Wait_Ack(void)
{
    MLX906_SDA_IN();//输入模式
    uint8_t utime=0;
    MLX906_SDA_H;
    Delay_us(1);
    MLX906_SCL_H;
    Delay_us(1);
    while(MLX906_READ_SDA())
    {
        utime++;
        if(utime>=255)
        {
            MLX906_STOP_Sign();
            return 1;//非应答信号
        }
    }
    MLX906_SCL_L;
    return 0;//应答信号
}
//主机应答（ACK信号）
void MLX906_Ack(void)
{
    
    MLX906_SDA_OUT();//输出模式
    MLX906_SDA_L;
    MLX906_SCL_L;
    Delay_us(2);
    MLX906_SCL_H;
    Delay_us(2);
    MLX906_SCL_L;
}
//不产生ACK应答信号
void MLX906_Nack(void)
{
    MLX906_SDA_OUT();//输出模式
    MLX906_SCL_L;
    MLX906_SDA_H;
    Delay_us(2);
    MLX906_SCL_H;
    Delay_us(2);
    MLX906_SCL_L;
    Delay_us(2);
}
 
//读取一个字节
uint8_t MLX906_ReadByte(void)
{
    uint8_t byte=0;
    uint8_t i;
    MLX906_SDA_IN();//输入模式
    for(i=0;i<8;i++)
    {
        MLX906_SCL_H;//SCL高电平时读取数据
        if(MLX906_READ_SDA())
        {
            byte|= 1<<(7-i);
        }
        MLX906_SCL_L;//下降沿时从机修改数据
        Delay_us(2);
    }
    MLX906_Nack();
    return byte;
}
//发送一个字节数据
uint8_t MLX906_SendByte(uint8_t byte1)
{
    uint8_t i,byte;
    byte=byte1;
    MLX906_SDA_OUT();//输出模式
    for(i=0;i<8;i++)//高位先发
    {
        if(byte&0x80)
        {
            MLX906_SDA_H;
        }
        else
        {
            MLX906_SDA_L;
        }
        MLX906_SCL_H;
        Delay_us(2);
        MLX906_SCL_L;
        Delay_us(2);
        byte<<=1;
    }
    MLX906_SDA_H;//释放总线
    return MLX906_Wait_Ack();//等待响应
}
 
//crc校验
uint8_t CRC_Calculation(uint8_t pec[])
{
    uint8_t crc[6];//存放多项式
    uint8_t BitPosition = 47;
    uint8_t shift;
    uint8_t i,j,temp;
    do
    {
        crc[5]=0;
        crc[4]=0;
        crc[3]=0;
        crc[2]=0;
        crc[1]=0x01;
        crc[0]=0x07;
        BitPosition = 47;
        shift = 0;
        i=5;
        j=0;
        while((pec[i]&(0x80>>j))==0 && i>0)
        {
            BitPosition--;
            if(j<7)
            {
                j++;
            }
            else
            {
                j= 0x00;
                i--;
            }
        }
        shift= BitPosition-8;
        while(shift)
        {
            for(i=5;i<0xFF;i--)
            {
                if((crc[i-1]&0x80)&&(i>0))
                {
                    temp=1;
                }
                else
                {
                    temp=0;
                }
                crc[i]<<=1;
                crc[i]+=temp;
            }
            shift--;
        }
        for(i=0;i<=5;i++)
        {
            pec[i]^=crc[i];
        }
    }while(BitPosition>8);
    return pec[0];
}
//读内存
uint16_t MLX906_ReadMemory(void)
{
    uint8_t Pec,PecReg,ErrorCounter;
    uint8_t TempL=0;
    uint8_t TempH=0;
    uint8_t arr[6];
    ErrorCounter=0;
    do
    {
        ErrorCounter++;
        if(ErrorCounter==10)
        {
            return 0;
        }            
        MLX906_START_Sign();//起始信号
        if(MLX906_SendByte(0x00))//发送MLX90614地址
            continue;
        if(MLX906_SendByte(0x07))//发送读MLX90614 RAM地址
            continue;
        MLX906_START_Sign();//重新启动
        if(MLX906_SendByte(0x01))//发送数据采集命令
            continue;
        TempL=MLX906_ReadByte();//读取地位数据
        TempH=MLX906_ReadByte();//读取高位数据
        Pec=MLX906_ReadByte();//读取校验位
        MLX906_STOP_Sign();//停止信号
        arr[5]= 0x00;
        arr[4]= 0x07;
        arr[3]= 0x01;
        arr[2]= TempL;
        arr[1]= TempH;
        arr[0]= 0;
        PecReg=CRC_Calculation(arr);//计算CRC校验
    }while(PecReg!=Pec);
    return (uint16_t)((TempH<<8)|TempL);
}
//读温度
float MLX906_Read_Temp(void)
{
    return (float )MLX906_ReadMemory()*0.02-273.15;
}

