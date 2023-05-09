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


uint8_t read_buf[4096]= {0};
uint8_t write_buf[4096]= {0};
uint32_t i;

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}



/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	uint8_t flash_id = 0;
	
  LED_GPIO_Config();
	
	LED_BLUE;
  /*��ʼ��USART1*/
  Debug_USART_Config(); 

	printf("\r\n ��ӭʹ��  STM32 F407 �����塣\r\n");		 

	printf("\r\n ����һ��FLASH��д�������� \r\n");

	SPI_FLASH_Init();
	
	flash_id = SPI_FLASH_Read_ID();
	
 	printf("\r\n flash_id = 0x%x \r\n",flash_id);
	
/******************************** �������� ********************************/
	printf("\r\n ��ʼ���� \r\n");	
	SPI_FLASH_Erase_Sector(4096*0);	
	
	SPI_FLASH_Erase_Sector(4096*1);
	
	printf("\r\n ��ɲ��� \r\n");	
	SPI_FLASH_Read_Buff(0, read_buf, 4096);
	
	for(i=0;i<4096;i++)
		{
			//��������0xFF��˵���������ɹ���
			if(read_buf[i] != 0xFF)
				{
					printf("\r\n��⵽������ʧ��\r\n");
				}
		}		
	printf("\r\n ��⵽��������� \r\n");
/****************************************************************************/
	
/********************************** д����� **********************************/
  /* ��ʼ��Ҫд������� */
	for(i=0;i<4096;i++)
		{
			write_buf[i] = 0x55;
		}	
	printf("\r\n ��ʼд�� \r\n");
	SPI_FLASH_Write_Buff(0, write_buf, 4096);
	printf("\r\n ��⵽��д����� \r\n");
	
	SPI_FLASH_Read_Buff(0, read_buf, 4096);
	printf("\r\n ��ȡ��������: \r\n");
				
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

