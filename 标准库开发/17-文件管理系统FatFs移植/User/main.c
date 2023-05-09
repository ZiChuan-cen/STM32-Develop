/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  */ 


#include "stm32f4xx.h"
#include "bsp_debug_usart.h"
#include "bsp_spi_flash.h"
#include "bsp_led.h"
#include "ff.h"
#include <string.h>

/**************** ȫ�ֱ��� *********************************/
FATFS fs;
FRESULT res;
FIL fil;
UINT bw;
UINT br;

#define STR_WRITE		"FatFs�ļ��������"
char read_buff[100];

/***********************************************************/

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	LED_GPIO_Config();
	
	LED_BLUE;
/*********************************** ��ʼ��USART1 ***********************************/
	Debug_USART_Config(); 

	printf("\r\n ��ӭʹ��  STM32 F407 �����塣\r\n");		 

	printf("\r\n ����һ���ļ�ϵͳ��ֲʵ�� \r\n");
	
/**************************************************************************************/
		
/******************************** ��ʼ��FatFs ********************************/
	res = f_mount(&fs, "1:", 1);
	printf("\r\n f_mount_res = %d \r\n",res);
	
	if(res == FR_NO_FILESYSTEM)
	{
		//��ʽ��
		res = f_mkfs("1:", 0, 0);
		printf("\r\n f_mkfs_res = %d \r\n",res);
			
		//��ʽ��֮����Ҫ���¹����ļ�ϵͳ
		res = f_mount(NULL, "1:", 1);
		
		res = f_mount(&fs, "1:", 1);
	}	
/**************************************************************************************/

/*********************************** ������д���ļ�1 ***********************************/
#if 0
	//��һ���ļ�
	res = f_open(&fil, "1:message.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	printf("\r\n f_open_res = %d \r\n",res);
	
	//д�����
	res = f_write(&fil, STR_WRITE, strlen(STR_WRITE)+1, &bw);
	printf("\r\n f_write_res = %d	len = %d	bw = %d \r\n",res,strlen(STR_WRITE)+1,bw);
	
	//�ر�һ���ļ�
	res = f_close(&fil);
	printf("\r\n f_close_res = %d \r\n",res);
#endif
/**************************************************************************************/
	
/*********************************** ������д���ļ�2 ***********************************/
#if 1
	//��һ���ļ�
	res = f_open(&fil, "1:abcdefghijklmnopqrstuvwxyz.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	printf("\r\n �ļ��� = %d \r\n",res);
	
	//д�����
	res = f_write(&fil, STR_WRITE, strlen(STR_WRITE)+1, &bw);
	printf("\r\n �ļ�д�� = %d	len = %d	bw = %d \r\n",res,strlen(STR_WRITE)+1,bw);
	
	//�ر�һ���ļ�
	res = f_close(&fil);
	printf("\r\n �ļ��ر� = %d \r\n",res);
#endif
/**************************************************************************************/
	
/************************************** ��ȡ�ļ� **************************************/
#if 1
    //�ٴδ��ļ�
	res = f_open(&fil, "1:message.txt", FA_OPEN_EXISTING | FA_READ);
	printf("\r\n f_open_res = %d \r\n",res);
	
	//��ȡ����
	res = f_read(&fil, read_buff, 18, &br);
	printf("\r\n f_read_res = %d	br = %d \r\n",res,br);
	printf("\r\n ��ȡ�����ļ����ݣ�\r\n");
	printf("\r\n %s \r\n",read_buff);
	
	//�ر��ļ�
	res = f_close(&fil);
	printf("\r\n f_close_res = %d ���Խ��� \r\n",res);
#endif	
/**************************************************************************************/
	
	
	
		  
  while (1)
  {
		
  }  

}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}




/*********************************************END OF FILE**********************/

