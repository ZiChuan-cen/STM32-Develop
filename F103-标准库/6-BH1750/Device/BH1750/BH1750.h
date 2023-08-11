#ifndef __BH1750_H
#define __BH1750_H

#include "stm32f10x.h"

#define uchar unsigned char 
#define uint  unsigned int
	
extern uchar    BUF[8];                         //接收数据缓存区      	
extern int     dis_data;                        //变量		
extern int   mcy;             					//表示进位标志位

#define	  SlaveAddress   0x46   
/* 定义器件在IIC总线中的从地址,
   根据ALT  ADDRESS地址引脚不同修改
   ALT  ADDRESS引脚接地时地址为0x46
   接电源时地址为0xB8 */


#define SCL_High	GPIO_SetBits(GPIOB,GPIO_Pin_6) 
#define SCL_Low		GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define SDA_High	GPIO_SetBits(GPIOB,GPIO_Pin_7) 
#define SDA_Low		GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define sda   			GPIO_Pin_7
#define scl  	 		GPIO_Pin_6
#define bh1750_PORT 	GPIOB
#define BH1750_CLK		RCC_APB2Periph_GPIOB


void BH1750_Init(void);
float BH1750_Read_Value(void);
void BH1750_Write_Com(uchar REG_Address);		//写入指令
void BH1750_Read_Com(void);					//读取指令


#endif /* __BH1750_H */

