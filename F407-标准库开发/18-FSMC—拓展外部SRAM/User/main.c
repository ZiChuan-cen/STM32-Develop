#include "stm32f4xx.h"
#include "bsp_debug_usart.h"
#include "bsp_sram.h"


#define SRAM_BASE_ADDR	0x6c000000
#define INER_SRAM_ADDR  0x20001000

/*
�������� ������  __attribute((at(ָ���ı�����ַ)));
����Ϊȫ�ֱ���
��������ĳ�ʼֵ��Ч
����Ҫ����FSMC��ʼ��֮��
*/
uint8_t testvalue  __attribute((at(0x6c000040)));

 /**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	// ����volatile��ֹCPU�Ż�
	volatile uint8_t * p = (uint8_t *)SRAM_BASE_ADDR;
	volatile uint8_t * p_iner = (uint8_t *)INER_SRAM_ADDR;
	volatile uint16_t * p_16 = (uint16_t *)(SRAM_BASE_ADDR+10);
	volatile uint32_t * p_32 = (uint32_t *)(SRAM_BASE_ADDR+20);

	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/	
	Debug_USART_Config();    
	
	//��ʼ��FSMC
	FSMC_Config();
	
	/* ����һ���ַ��� */
	Usart_SendString( DEBUG_USART,"\r\n ����һ�������жϽ��ջ���ʵ�� \r\n");    
	
	printf("\r\n ����һ�������жϽ��ջ���ʵ�� \r\n");
	
/*********************************************************************************************/	
	//д�����
	*p = 0xFE;	
	//��ȡ����
	printf("\r\n pд�������Ϊ��0x%x \r\n", *p);
	
	//д�����
	*p_iner = 0x77;	
	//��ȡ����
	printf("\r\n p_inerд�������Ϊ��0x%x \r\n", *p_iner);
	
	//д�����
	*p_16 = 0xABcd;	
	//��ȡ����
	printf("\r\n p_16д�������Ϊ��0x%x \r\n", *p_16);
	
	//д�����
	*p_32 = 0x111111;	
	//��ȡ����
	printf("\r\n p_32д�������Ϊ��0x%x \r\n", *p_32);\
	
	//д�����
	testvalue = 4;	
	//��ȡ����
	printf("\r\n testvalueд�������Ϊ��0x%x ,���ַΪ:0x%x \r\n", testvalue, &testvalue);
/*********************************************************************************************/	
  while(1)
	{	
		
	}	
}


