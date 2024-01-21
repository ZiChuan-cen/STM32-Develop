#ifndef _ADXL345_H
#define _ADXL345_H

#include "stm32f10x.h"

#define ADXL345_GPIO 	 	GPIOB
#define ADXL345_GPIOCLK  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)
#define ADXL345_SDA   		GPIO_Pin_15
#define ADXL345_SCL   		GPIO_Pin_14


extern uint8_t Angle_flag0 ;            //当前状态 0跌倒 1正常
extern int  ADXL345_y ;                 //y轴的角度
extern int  ADXL345_x ;
extern int  ADXL345_z ;
extern void Angle(void);                //判断状态

#define SCL_0 GPIO_ResetBits(ADXL345_GPIO, ADXL345_SCL)
#define SCL_1 GPIO_SetBits(ADXL345_GPIO, ADXL345_SCL)
#define SDA_0 GPIO_ResetBits(ADXL345_GPIO, ADXL345_SDA)
#define SDA_1 GPIO_SetBits(ADXL345_GPIO, ADXL345_SDA)

#define ADXL345SDA	GPIO_ReadInputDataBit(ADXL345_GPIO, ADXL345_SDA)


#define SlaveAddress   0xA6   //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改

void ADXL_345_ALL_Int(void);
unsigned char ADXL345_RecvACK(void);
unsigned char ADXL345_Recvbyte(void);
void ADXL345_SDA_Intput(void);
void ADXL345_SDA_Output(void);
void ADXL345_SendACK(unsigned char ack);
void ADXL345_Sendbyte(unsigned char dat);
void ADXL345_Start(void);
void ADXL345_Stop(void);
void Init_ADXL345(void);
void Multiple_ReadADXL345(void);
unsigned char Single_Read_ADXL345(unsigned char REG_Address);
void Single_Write_ADXL345(unsigned char REG_Address, unsigned char REG_data);


void Angle(void);


#endif
