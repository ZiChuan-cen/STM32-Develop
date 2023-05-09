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


uint8_t read_buf[4096]= {0};
uint8_t write_buf[4096]= {0};
uint32_t i;

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}



/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	uint8_t flash_id = 0;
	
  LED_GPIO_Config();
	
	LED_BLUE;
  /*初始化USART1*/
  Debug_USART_Config(); 

	printf("\r\n 欢迎使用  STM32 F407 开发板。\r\n");		 

	printf("\r\n 这是一个FLASH读写测试例程 \r\n");

	SPI_FLASH_Init();
	
	flash_id = SPI_FLASH_Read_ID();
	
 	printf("\r\n flash_id = 0x%x \r\n",flash_id);
	
/******************************** 擦除测试 ********************************/
	printf("\r\n 开始擦除 \r\n");	
	SPI_FLASH_Erase_Sector(4096*0);	
	
	SPI_FLASH_Erase_Sector(4096*1);
	
	printf("\r\n 完成擦除 \r\n");	
	SPI_FLASH_Read_Buff(0, read_buf, 4096);
	
	for(i=0;i<4096;i++)
		{
			//若不等于0xFF，说明擦除不成功，
			if(read_buf[i] != 0xFF)
				{
					printf("\r\n检测到：擦除失败\r\n");
				}
		}		
	printf("\r\n 检测到：擦除完成 \r\n");
/****************************************************************************/
	
/********************************** 写入测试 **********************************/
  /* 初始化要写入的数据 */
	for(i=0;i<4096;i++)
		{
			write_buf[i] = 0x55;
		}	
	printf("\r\n 开始写入 \r\n");
	SPI_FLASH_Write_Buff(0, write_buf, 4096);
	printf("\r\n 检测到：写入完成 \r\n");
	
	SPI_FLASH_Read_Buff(0, read_buf, 4096);
	printf("\r\n 读取到的数据: \r\n");
				
	for(i=0;i</*256*/4096;i++)
		{
			printf("0x%02x ",read_buf[i]);
			//Delay(0xfffff);
		}
/*********************************************************************************/	
		  
  while (1)
  {
		
  }  

}




/*********************************************END OF FILE**********************/

