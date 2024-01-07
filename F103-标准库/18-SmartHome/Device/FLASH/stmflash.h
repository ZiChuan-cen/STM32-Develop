#ifndef __STMFLASH_H
#define __STMFLASH_H	 
#include "sys.h"

#define STM32_FLASH_SIZE 64 	 		//��ѡSTM32��FLASH������С(��λΪK)stm32f103c8t6(64k)
#define STM32_FLASH_WREN 1              //ʹ��FLASHд��(0��������;1��ʹ��)

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //��������  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

//����д��
void u16_Write(u32 WriteAddr,u16 WriteData);			


#endif

