#ifndef _MLX90614_H_
#define _MLX90614_H_
 
#include "stm32f10x.h"
//#include "systick.h"
//#include "sys.h"
/*
引脚连接：
    SCL  时钟线  - PB10
    SDA     数据线  - PB11
*/

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 


#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 


#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 




#define MLX906_SCL_H GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET)
#define MLX906_SCL_L GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET)
#define MLX906_SDA_H GPIO_WriteBit(GPIOB,GPIO_Pin_9,Bit_SET)
#define MLX906_SDA_L GPIO_WriteBit(GPIOB,GPIO_Pin_9,Bit_RESET)
#define MLX906_READ_SDA() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
 
//配置SDA数据线的输入输出模式
#define MLX906_SDA_OUT() PBout(9)//输出模式 自己配置哦
#define MLX906_SDA_IN()  PBin(9)//输入模式
 
//此处为笔者小设计中才用到的，不用管
#define MLX906_STATE_READ 1
#define MLX906_STATE_UNREAD 0
#define ANOMALY_TEMP 37     //体温异常
 
extern float MLX906_Temp;
extern uint8_t  MLX906_Temp_State;
 
void MLX906_Init(void);
float MLX906_Read_Temp(void);
 
#endif

