#ifndef __STMFLASH_H
#define __STMFLASH_H	 
#include "sys.h"

#define STM32_FLASH_SIZE 64 	 		//所选STM32的FLASH容量大小(单位为K)stm32f103c8t6(64k)
#define STM32_FLASH_WREN 1              //使能FLASH写入(0，不是能;1，使能)

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //读出半字  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//指定地址开始写入指定长度的数据
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//指定地址开始读取指定长度数据
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//从指定地址开始读出指定长度的数据

//测试写入
void u16_Write(u32 WriteAddr,u16 WriteData);			


#endif

