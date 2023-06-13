/**
  ******************************************************************************
  * @file    bsp_spi_flash.c
  * @author  zichuan
  * @version 1.0
  * @date    2023.04.11
  * @brief   SPI	FLASH	应用函数bsp
  ******************************************************************************
	*
	*	实验平台:STM32	F407	VGT6	开发板
	*
	*
  */

#include "bsp_spi_flash.h"
#include "bsp_debug_usart.h"

/**
	*1.初始化相关引脚及SPI工作模式
	*2.编写基本的读写单个字节的流程函数
	*3.利用2的函数来组成各种命令
	*4.利用命令读写FLASH并校验数据
	*
*/




static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;   


static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);




/**
  * @brief  SPI I/O配置
  * @param  无
  * @retval 无
  */
static void SPI_GPIO_Config(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure; 
   
  /*!< FLASH_SPI Periph clock enable */
  FLASH_SPI_CLK_INIT(FLASH_SPI_CLK, ENABLE);
  
  /* 使能 FLASH 引脚时钟 */
  RCC_AHB1PeriphClockCmd(FLASH_SPI_SCK_GPIO_CLK 
												| FLASH_SPI_MISO_GPIO_CLK
												| FLASH_SPI_MOSI_GPIO_CLK
												| FLASH_SPI_CS_GPIO_CLK,
												ENABLE);

  //配置 SCK MISO MOSI 引脚源
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
	
	/* 使用软件控制CS引脚 */   
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(FLASH_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
 
}

/**
  * @brief  SPI 工作模式配置
  * @param  无
  * @retval 无
  */
static void SPI_Mode_Config(void)
{
  SPI_InitTypeDef  SPI_InitStructure; 
	
	
  /* SPI1 配置 */
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
  SPI_Cmd(FLASH_SPI, ENABLE); 															/* 使能	SPI1 */
}

/**
  * @brief  SPI 外设(FLASH)初始化
  * @param  无
  * @retval 无
  */
void SPI_FLASH_Init(void)
{
  SPI_GPIO_Config(); 
 
  SPI_Mode_Config();


}



/**
  * @brief   通过SPI发送一个字节
  * @param 
  *		@arg data:写地址 
  * @retval  接收到的数据
  */
uint8_t SPI_FLASH_ByteWrite(uint8_t data)
{
	uint8_t  re_data;
	
	//等待TXE标志
	SPITimeout = SPIT_FLAG_TIMEOUT;
  while(SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE)  == RESET )
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
  }
	
	
	SPI_I2S_SendData(FLASH_SPI, data);
	
	//等待RXNE标志  来确认发送完成  及准备读取数据
	SPITimeout = SPIT_FLAG_TIMEOUT;
	while(SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE)  == RESET )
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
  }
	
	re_data = SPI_I2S_ReceiveData(FLASH_SPI);
	
	return re_data;
	
}

/**
  * @brief   读取FLASH ID
  * @param   读ID0 - ID7
  *		@arg 
  * @retval  ID
  */
uint8_t SPI_FLASH_Read_ID(void)
{
	uint8_t id;
	
	//控制片选引脚
	FLASH_SPI_CS_LOW();	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_ReleasePowerDown);	
	SPI_FLASH_ByteWrite(DUMMY);	
	SPI_FLASH_ByteWrite(DUMMY);
	SPI_FLASH_ByteWrite(DUMMY);	
	//接收读取到的内容	
	id = SPI_FLASH_ByteWrite(DUMMY);
	FLASH_SPI_CS_HIGH();	
	return id;
}


/**
  * @brief   擦除扇区  
  * @param 
  *		@arg addr:必须对齐要擦除扇区的首地址
  * @retval  接收到的数据
  */
void SPI_FLASH_Erase_Sector(uint32_t addr)
{
	SPI_FLASH_Write_Enable();
	
	//控制片选引脚
	FLASH_SPI_CS_LOW();	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_SectorErase);	
	//发送要擦除的地址
	SPI_FLASH_ByteWrite((addr >> 16) & 0xFF);	
	SPI_FLASH_ByteWrite((addr >> 8) & 0xFF);
	SPI_FLASH_ByteWrite((addr >> 0) & 0xFF); 
	FLASH_SPI_CS_HIGH();	
	
	//等待内部时序完成
	SPI_FLASH_Wait_For_Standby();

}

/**
  * @brief   读取数据 
  * @param 
  *		@arg addr:要读取数据的首地址
	*   @arg buf:存储读取到的数据的指针
*   @arg size:要读取多少个数据
  * @retval  
  */
void SPI_FLASH_Read_Buff(uint32_t addr, uint8_t *buf, uint32_t size)
{
	//控制片选引脚
	FLASH_SPI_CS_LOW();	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_ReadData);	
	//发送要读取的地址
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
  * @brief   写入数据 
  * @param 
  *		@arg addr:要写入数据的首地址
	*   @arg buf:要写入数据的指针
*   @arg size:要写入多少个数据		不能超过256
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
	    //等待内部时序完成
			SPI_FLASH_Wait_For_Standby();
			
	  	//写使能
			SPI_FLASH_Write_Enable();
			
			//控制片选引脚
			FLASH_SPI_CS_LOW();	
			//指令代码
			SPI_FLASH_ByteWrite(W25X_PageProgram);	
			
			//发送要写入的地址
			SPI_FLASH_ByteWrite((addr >> 16) & 0xFF);	
			SPI_FLASH_ByteWrite((addr >> 8) & 0xFF);
			SPI_FLASH_ByteWrite((addr >> 0) & 0xFF); 
		}
		//发送要写入的数据	
		SPI_FLASH_ByteWrite(*buf); 
		buf++;
		addr++;		
	}
	FLASH_SPI_CS_HIGH();
	//等待内部时序完成
	SPI_FLASH_Wait_For_Standby();
}



/**
  * @brief   写使能
  * @param 
  *		@arg 
  * @retval  
  */
void SPI_FLASH_Write_Enable(void)
{
	
	/******************** 在写入操作之前一定要执行Write Enable指令 ********************/
	//控制片选引脚
	FLASH_SPI_CS_LOW();	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_WriteEnable);	   
	FLASH_SPI_CS_HIGH();          // !!!!!!!!!!!!!!!!!!!!引脚拉高,代表命令结束
	/****************************************************************************/
	
}


/**
  * @brief   等待直到空闲状态
  * @param 
  *		@arg 
  * @retval  
  */
void SPI_FLASH_Wait_For_Standby(void)
{
	uint8_t status;
	/******************** 在写入操作之前一定要执行Write Enable指令 ********************/
	//控制片选引脚
	FLASH_SPI_CS_LOW();	
	//指令代码
	SPI_FLASH_ByteWrite(W25X_ReadStatusReg);	
	
	
	SPITimeout = SPIT_LONG_TIMEOUT;
	while(1)
	{
		status = SPI_FLASH_ByteWrite(DUMMY);	  
		//如果条件成立，说明为忙碌状态
		if((status & 0x01)  == 0)
		{
			break;
		}
		//若SPITimeout为0，表示已检测SPITimeout次仍为busy，跳出循环
		if((SPITimeout--) == 0)
    {
			SPI_TIMEOUT_UserCallback(3);
			break;
		}			
	}
	FLASH_SPI_CS_HIGH();          // !!!!!!!!!!!!!!!!!!!!引脚拉高,代表命令结束
	/****************************************************************************/	
}





/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode：错误代码，可以用来定位是哪个环节出错.
  * @retval 返回0，表示SPI读取失败.
  */
static  uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  FALSH_ERROR("SPI 等待超时!errorCode = %d",errorCode);
  
  return 0;
}
/*********************************************END OF FILE**********************/
