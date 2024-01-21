#include "mlx90614.h"
#include "delay.h"
 
//MLX��ʼ������
void MLX906_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//��GPIOBʱ��
    //��ʼ������
    GPIO_InitTypeDef mlx906_gpio_init;
    mlx906_gpio_init.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
    mlx906_gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    mlx906_gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&mlx906_gpio_init);
    
    MLX906_SCL_H;//�������ŵ�ƽ
    MLX906_SDA_H;
}
 
/*    IIC   ʱ��    */
 
//��ʼ�ź�
void MLX906_START_Sign(void)
{
    MLX906_SDA_OUT();//���ģʽ
    MLX906_SDA_H;
    MLX906_SCL_H;
    Delay_us(2);
    MLX906_SDA_L;
    Delay_us(2);
    MLX906_SCL_L;//ǯס���ߣ�׼����ʼ���ݴ���
    Delay_us(1);
}
//ֹͣ�ź�
void MLX906_STOP_Sign(void)
{
    MLX906_SDA_OUT();//���ģʽ
    MLX906_SCL_L;
    MLX906_SDA_L;
    Delay_us(2);
    MLX906_SCL_H;
    MLX906_SDA_H;
    Delay_us(1);
}
uint8_t MLX906_Wait_Ack(void)
{
    MLX906_SDA_IN();//����ģʽ
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
            return 1;//��Ӧ���ź�
        }
    }
    MLX906_SCL_L;
    return 0;//Ӧ���ź�
}
//����Ӧ��ACK�źţ�
void MLX906_Ack(void)
{
    
    MLX906_SDA_OUT();//���ģʽ
    MLX906_SDA_L;
    MLX906_SCL_L;
    Delay_us(2);
    MLX906_SCL_H;
    Delay_us(2);
    MLX906_SCL_L;
}
//������ACKӦ���ź�
void MLX906_Nack(void)
{
    MLX906_SDA_OUT();//���ģʽ
    MLX906_SCL_L;
    MLX906_SDA_H;
    Delay_us(2);
    MLX906_SCL_H;
    Delay_us(2);
    MLX906_SCL_L;
    Delay_us(2);
}
 
//��ȡһ���ֽ�
uint8_t MLX906_ReadByte(void)
{
    uint8_t byte=0;
    uint8_t i;
    MLX906_SDA_IN();//����ģʽ
    for(i=0;i<8;i++)
    {
        MLX906_SCL_H;//SCL�ߵ�ƽʱ��ȡ����
        if(MLX906_READ_SDA())
        {
            byte|= 1<<(7-i);
        }
        MLX906_SCL_L;//�½���ʱ�ӻ��޸�����
        Delay_us(2);
    }
    MLX906_Nack();
    return byte;
}
//����һ���ֽ�����
uint8_t MLX906_SendByte(uint8_t byte1)
{
    uint8_t i,byte;
    byte=byte1;
    MLX906_SDA_OUT();//���ģʽ
    for(i=0;i<8;i++)//��λ�ȷ�
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
    MLX906_SDA_H;//�ͷ�����
    return MLX906_Wait_Ack();//�ȴ���Ӧ
}
 
//crcУ��
uint8_t CRC_Calculation(uint8_t pec[])
{
    uint8_t crc[6];//��Ŷ���ʽ
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
//���ڴ�
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
        MLX906_START_Sign();//��ʼ�ź�
        if(MLX906_SendByte(0x00))//����MLX90614��ַ
            continue;
        if(MLX906_SendByte(0x07))//���Ͷ�MLX90614 RAM��ַ
            continue;
        MLX906_START_Sign();//��������
        if(MLX906_SendByte(0x01))//�������ݲɼ�����
            continue;
        TempL=MLX906_ReadByte();//��ȡ��λ����
        TempH=MLX906_ReadByte();//��ȡ��λ����
        Pec=MLX906_ReadByte();//��ȡУ��λ
        MLX906_STOP_Sign();//ֹͣ�ź�
        arr[5]= 0x00;
        arr[4]= 0x07;
        arr[3]= 0x01;
        arr[2]= TempL;
        arr[1]= TempH;
        arr[0]= 0;
        PecReg=CRC_Calculation(arr);//����CRCУ��
    }while(PecReg!=Pec);
    return (uint16_t)((TempH<<8)|TempL);
}
//���¶�
float MLX906_Read_Temp(void)
{
    return (float )MLX906_ReadMemory()*0.02-273.15;
}

