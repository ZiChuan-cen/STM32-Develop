#include "stm32f4xx.h"
#include "bsp_debug_usart.h"
#include "bsp_sram.h"


#define SRAM_BASE_ADDR	0x6c000000
#define INER_SRAM_ADDR  0x20001000

/*
变量类型 变量名  __attribute((at(指定的变量地址)));
必须为全局变量
变量定义的初始值无效
必须要放在FSMC初始化之后
*/
uint8_t testvalue  __attribute((at(0x6c000040)));

 /**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	// 加入volatile防止CPU优化
	volatile uint8_t * p = (uint8_t *)SRAM_BASE_ADDR;
	volatile uint8_t * p_iner = (uint8_t *)INER_SRAM_ADDR;
	volatile uint16_t * p_16 = (uint16_t *)(SRAM_BASE_ADDR+10);
	volatile uint32_t * p_32 = (uint32_t *)(SRAM_BASE_ADDR+20);

	/*初始化USART 配置模式为 115200 8-N-1，中断接收*/	
	Debug_USART_Config();    
	
	//初始化FSMC
	FSMC_Config();
	
	/* 发送一个字符串 */
	Usart_SendString( DEBUG_USART,"\r\n 这是一个串口中断接收回显实验 \r\n");    
	
	printf("\r\n 这是一个串口中断接收回显实验 \r\n");
	
/*********************************************************************************************/	
	//写入操作
	*p = 0xFE;	
	//读取操作
	printf("\r\n p写入的数据为：0x%x \r\n", *p);
	
	//写入操作
	*p_iner = 0x77;	
	//读取操作
	printf("\r\n p_iner写入的数据为：0x%x \r\n", *p_iner);
	
	//写入操作
	*p_16 = 0xABcd;	
	//读取操作
	printf("\r\n p_16写入的数据为：0x%x \r\n", *p_16);
	
	//写入操作
	*p_32 = 0x111111;	
	//读取操作
	printf("\r\n p_32写入的数据为：0x%x \r\n", *p_32);\
	
	//写入操作
	testvalue = 4;	
	//读取操作
	printf("\r\n testvalue写入的数据为：0x%x ,其地址为:0x%x \r\n", testvalue, &testvalue);
/*********************************************************************************************/	
  while(1)
	{	
		
	}	
}


