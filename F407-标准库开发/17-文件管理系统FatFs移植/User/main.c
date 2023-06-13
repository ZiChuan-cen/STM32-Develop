/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  */ 


#include "stm32f4xx.h"
#include "bsp_debug_usart.h"
#include "bsp_spi_flash.h"
#include "bsp_led.h"
#include "ff.h"
#include <string.h>

/**************** 全局变量 *********************************/
FATFS fs;
FRESULT res;
FIL fil;
UINT bw;
UINT br;

#define STR_WRITE		"FatFs文件管理测试"
char read_buff[100];

/***********************************************************/

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	LED_GPIO_Config();
	
	LED_BLUE;
/*********************************** 初始化USART1 ***********************************/
	Debug_USART_Config(); 

	printf("\r\n 欢迎使用  STM32 F407 开发板。\r\n");		 

	printf("\r\n 这是一个文件系统移植实验 \r\n");
	
/**************************************************************************************/
		
/******************************** 初始化FatFs ********************************/
	res = f_mount(&fs, "1:", 1);
	printf("\r\n f_mount_res = %d \r\n",res);
	
	if(res == FR_NO_FILESYSTEM)
	{
		//格式化
		res = f_mkfs("1:", 0, 0);
		printf("\r\n f_mkfs_res = %d \r\n",res);
			
		//格式化之后需要重新挂载文件系统
		res = f_mount(NULL, "1:", 1);
		
		res = f_mount(&fs, "1:", 1);
	}	
/**************************************************************************************/

/*********************************** 创建并写入文件1 ***********************************/
#if 0
	//打开一个文件
	res = f_open(&fil, "1:message.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	printf("\r\n f_open_res = %d \r\n",res);
	
	//写入操作
	res = f_write(&fil, STR_WRITE, strlen(STR_WRITE)+1, &bw);
	printf("\r\n f_write_res = %d	len = %d	bw = %d \r\n",res,strlen(STR_WRITE)+1,bw);
	
	//关闭一个文件
	res = f_close(&fil);
	printf("\r\n f_close_res = %d \r\n",res);
#endif
/**************************************************************************************/
	
/*********************************** 创建并写入文件2 ***********************************/
#if 1
	//打开一个文件
	res = f_open(&fil, "1:abcdefghijklmnopqrstuvwxyz.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	printf("\r\n 文件打开 = %d \r\n",res);
	
	//写入操作
	res = f_write(&fil, STR_WRITE, strlen(STR_WRITE)+1, &bw);
	printf("\r\n 文件写入 = %d	len = %d	bw = %d \r\n",res,strlen(STR_WRITE)+1,bw);
	
	//关闭一个文件
	res = f_close(&fil);
	printf("\r\n 文件关闭 = %d \r\n",res);
#endif
/**************************************************************************************/
	
/************************************** 读取文件 **************************************/
#if 1
    //再次打开文件
	res = f_open(&fil, "1:message.txt", FA_OPEN_EXISTING | FA_READ);
	printf("\r\n f_open_res = %d \r\n",res);
	
	//读取操作
	res = f_read(&fil, read_buff, 18, &br);
	printf("\r\n f_read_res = %d	br = %d \r\n",res,br);
	printf("\r\n 读取到的文件内容：\r\n");
	printf("\r\n %s \r\n",read_buff);
	
	//关闭文件
	res = f_close(&fil);
	printf("\r\n f_close_res = %d 测试结束 \r\n",res);
#endif	
/**************************************************************************************/
	
	
	
		  
  while (1)
  {
		
  }  

}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}




/*********************************************END OF FILE**********************/

