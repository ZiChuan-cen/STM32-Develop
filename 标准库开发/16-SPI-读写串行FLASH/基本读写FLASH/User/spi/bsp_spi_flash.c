/**
  ******************************************************************************
  * @file    bsp_spi_flash.c
  * @author  zichuan
  * @version 1.0
  * @date    2023.04.11
  * @brief   SPI	FLASH	Ӧ�ú���bsp
  ******************************************************************************
	*
	*	ʵ��ƽ̨:STM32	F407	VGT6	������
	*
	*
  */

#include "bsp_spi_flash.h"
#include "bsp_debug_usart.h"

/**
	*1.��ʼ��������ż�SPI����ģʽ
	*2.��д�����Ķ�д�����ֽڵ����̺���
	*3.����2�ĺ�������ɸ�������
	*4.���������дFLASH��У������
	*
*/




static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;   


static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);




/**
  * @brief  SPI I/O����
  * @param  ��
  * @retval ��
  */
static void SPI_GPIO_Config(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure; 
   
  /*!< FLASH_SPI Periph clock enable */
  FLASH_SPI_CLK_INIT(FLASH_SPI_CLK, ENABLE);
  
  /* ʹ�� FLASH ����ʱ�� */
  RCC_AHB1PeriphClockCmd(FLASH_SPI_SCK_GPIO_CLK 
												| FLASH_SPI_MISO_GPIO_CLK
												| FLASH_SPI_MOSI_GPIO_CLK
												| FLASH_SPI_CS_GPIO_CLK,
												ENABLE);

  //���� SCK MISO MOSI ����Դ
  GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT, FLASH_SPI_SCK_SOURCE, FLASH_SPI_SCK_AF);
	
	GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT, FLASH_SPI_MISO_SOURCE, FLASH_SPI_MISO_AF);
	
	GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT, FLASH_SPI_MOSI_SOURCE, FLASH_SPI_MOSI_AF);
	
	
  
  
  /*!< Configure FLASH_SPI pins: SCK */   
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure FLASH_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
  GPIO_Init(FLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
	
	/*!< Configure FLASH_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
  GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
	
	/* ʹ���������CS���� */   
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(FLASH_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
 
}

/**
  * @brief  SPI ����ģʽ����
  * @param  ��
  * @retval ��
  */
static void SPI_Mode_Config(void)
{
  SPI_InitTypeDef  SPI_InitStructure; 
	
	
  /* SPI1 ���� */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = 0;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//W25Q128
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	
  
  SPI_Init(FLASH_SPI, &SPI_InitStructure);                                      
  SPI_Cmd(FLASH_SPI, ENABLE); 															/* ʹ��	SPI1 */
}

/**
  * @brief  SPI ����(FLASH)��ʼ��
  * @param  ��
  * @retval ��
  */
void SPI_FLASH_Init(void)
{
  SPI_GPIO_Config(); 
 
  SPI_Mode_Config();


}



/**
  * @brief   ͨ��SPI����һ���ֽ�
  * @param 
  *		@arg data:д��ַ 
  * @retval  ���յ�������
  */
uint8_t SPI_FLASH_ByteWrite(uint8_t data)
{
	uint8_t  re_data;
	
	//�ȴ�TXE��־
	SPITimeout = SPIT_FLAG_TIMEOUT;
  while(SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE)  == RESET )
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
  }
	
	
	SPI_I2S_SendData(FLASH_SPI, data);
	
	//�ȴ�RXNE��־  ��ȷ�Ϸ������  ��׼����ȡ����
	SPITimeout = SPIT_FLAG_TIMEOUT;
	while(SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE)  == RESET )
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
  }
	
	re_data = SPI_I2S_ReceiveData(FLASH_SPI);
	
	return re_data;
	
}

/**
  * @brief   ��ȡFLASH ID
  * @param   ��ID0 - ID7
  *		@arg 
  * @retval  ID
  */
uint8_t SPI_FLASH_Read_ID(void)
{
	uint8_t id;
	
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_ReleasePowerDown);	
	SPI_FLASH_ByteWrite(DUMMY);	
	SPI_FLASH_ByteWrite(DUMMY);
	SPI_FLASH_ByteWrite(DUMMY);	
	//���ն�ȡ��������	
	id = SPI_FLASH_ByteWrite(DUMMY);
	FLASH_SPI_CS_HIGH();	
	return id;
}


/**
  * @brief   ��������  
  * @param 
  *		@arg addr:�������Ҫ�����������׵�ַ
  * @retval  ���յ�������
  */
void SPI_FLASH_Erase_Sector(uint32_t addr)
{
	SPI_FLASH_Write_Enable();
	
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_SectorErase);	
	//����Ҫ�����ĵ�ַ
	SPI_FLASH_ByteWrite((addr >> 16) & 0xFF);	
	SPI_FLASH_ByteWrite((addr >> 8) & 0xFF);
	SPI_FLASH_ByteWrite((addr >> 0) & 0xFF); 
	FLASH_SPI_CS_HIGH();	
	
	//�ȴ��ڲ�ʱ�����
	SPI_FLASH_Wait_For_Standby();

}

/**
  * @brief   ��ȡ���� 
  * @param 
  *		@arg addr:Ҫ��ȡ���ݵ��׵�ַ
	*   @arg buf:�洢��ȡ�������ݵ�ָ��
*   @arg size:Ҫ��ȡ���ٸ�����
  * @retval  
  */
void SPI_FLASH_Read_Buff(uint32_t addr, uint8_t *buf, uint32_t size)
{
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_ReadData);	
	//����Ҫ��ȡ�ĵ�ַ
	SPI_FLASH_ByteWrite((addr >> 16) & 0xFF);	
	SPI_FLASH_ByteWrite((addr >> 8) & 0xFF);
	SPI_FLASH_ByteWrite((addr >> 0) & 0xFF); 
	
	while(size--)
		{
			*buf = SPI_FLASH_ByteWrite(DUMMY);
		  buf++;
		}
	
	FLASH_SPI_CS_HIGH();

}


/**
  * @brief   д������ 
  * @param 
  *		@arg addr:Ҫд�����ݵ��׵�ַ
	*   @arg buf:Ҫд�����ݵ�ָ��
*   @arg size:Ҫд����ٸ�����		���ܳ���256
  * @retval  
  */
void SPI_FLASH_Write_Buff(uint32_t addr, uint8_t *buf, uint32_t size)
{
	uint32_t count = 0;
	while(size--)
	{
		count++;
		if(count == 1 || (count % 256)  == 1 || (addr % 4096) == 0)
		{
			FLASH_SPI_CS_HIGH();
	    //�ȴ��ڲ�ʱ�����
			SPI_FLASH_Wait_For_Standby();
			
	  	//дʹ��
			SPI_FLASH_Write_Enable();
			
			//����Ƭѡ����
			FLASH_SPI_CS_LOW();	
			//ָ�����
			SPI_FLASH_ByteWrite(W25X_PageProgram);	
			
			//����Ҫд��ĵ�ַ
			SPI_FLASH_ByteWrite((addr >> 16) & 0xFF);	
			SPI_FLASH_ByteWrite((addr >> 8) & 0xFF);
			SPI_FLASH_ByteWrite((addr >> 0) & 0xFF); 
		}
		//����Ҫд�������	
		SPI_FLASH_ByteWrite(*buf); 
		buf++;
		addr++;		
	}
	FLASH_SPI_CS_HIGH();
	//�ȴ��ڲ�ʱ�����
	SPI_FLASH_Wait_For_Standby();
}



/**
  * @brief   дʹ��
  * @param 
  *		@arg 
  * @retval  
  */
void SPI_FLASH_Write_Enable(void)
{
	
	/******************** ��д�����֮ǰһ��Ҫִ��Write Enableָ�� ********************/
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_WriteEnable);	   
	FLASH_SPI_CS_HIGH();          // !!!!!!!!!!!!!!!!!!!!��������,�����������
	/****************************************************************************/
	
}


/**
  * @brief   �ȴ�ֱ������״̬
  * @param 
  *		@arg 
  * @retval  
  */
void SPI_FLASH_Wait_For_Standby(void)
{
	uint8_t status;
	/******************** ��д�����֮ǰһ��Ҫִ��Write Enableָ�� ********************/
	//����Ƭѡ����
	FLASH_SPI_CS_LOW();	
	//ָ�����
	SPI_FLASH_ByteWrite(W25X_ReadStatusReg);	
	
	
	SPITimeout = SPIT_LONG_TIMEOUT;
	while(1)
	{
		status = SPI_FLASH_ByteWrite(DUMMY);	  
		//�������������˵��Ϊæµ״̬
		if((status & 0x01)  == 0)
		{
			break;
		}
		//��SPITimeoutΪ0����ʾ�Ѽ��SPITimeout����Ϊbusy������ѭ��
		if((SPITimeout--) == 0)
    {
			SPI_TIMEOUT_UserCallback(3);
			break;
		}			
	}
	FLASH_SPI_CS_HIGH();          // !!!!!!!!!!!!!!!!!!!!��������,�����������
	/****************************************************************************/	
}





/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode��������룬����������λ���ĸ����ڳ���.
  * @retval ����0����ʾSPI��ȡʧ��.
  */
static  uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  FALSH_ERROR("SPI �ȴ���ʱ!errorCode = %d",errorCode);
  
  return 0;
}
/*********************************************END OF FILE**********************/
