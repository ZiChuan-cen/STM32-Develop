/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "bsp_spi_flash.h"

//定义逻辑设备号
#define SD_CARD		0
#define SPI_FLASH	1

#define FLASH_SECTOR_SIZE		4096


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = 0;
	uint32_t spi_result;

	switch (pdrv) {
	case SD_CARD :
		//SD卡状态返回分支		
		return stat;
	case SPI_FLASH :
		//SPI_FLASH状态返回分支
		spi_result = SPI_FLASH_Read_ID();		
		if(spi_result == 0x16)
		{
			stat &= ~STA_NOINIT;		//stat最低位为0，表示SPI FLASH 为正常状态
		}
		else
		{
			stat |= STA_NOINIT;		//stat最低位为1，表示SPI FLASH 为不正常状态
		}
		return stat;
//	case USB :
//		//USB状态返回分支
//		result = USB_disk_status();
//		// translate the reslut code here
//		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	
	switch (pdrv) {
	case SD_CARD :
		//SD卡初始化分支
		return stat;
	case SPI_FLASH :
		//SPI_FLASH初始化分支
		SPI_FLASH_Init();
		stat = disk_status(SPI_FLASH);
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	switch (pdrv) {
	case SD_CARD :		//SD读取分支
		return res;
	
	case SPI_FLASH :		//SPI_FLASH读取分支		
		SPI_FLASH_Read_Buff((uint8_t*)buff, sector*FLASH_SECTOR_SIZE, count*FLASH_SECTOR_SIZE);
						//sector*FLASH_SECTOR_SIZE;		把要读取的扇区号转换成地址
	
		return RES_OK;		//默认每次都能正常读取
		}
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;

	switch (pdrv) {
	case SD_CARD :		//SD写入分支
		return res;
	case SPI_FLASH :	//SPI_FLASH写入分支	
		while(count--)
		{
			SPI_FLASH_Erase_Sector(sector*FLASH_SECTOR_SIZE);		//写入前先擦除
			
			SPI_FLASH_Write_Buff((uint8_t*)buff, sector*FLASH_SECTOR_SIZE, 1*FLASH_SECTOR_SIZE);
					//sector*FLASH_SECTOR_SIZE:把要写入的扇区号转换成地址
			sector++;
			buff += FLASH_SECTOR_SIZE;
		}
		return RES_OK;		//默认每次都能正常读取
		}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	
	switch(pdrv) 
	{
		case SD_CARD :		//SD分支
			
			return res;
		case SPI_FLASH :		//SPI_FLASH分支	
			
			switch(cmd)
			{			
				case GET_SECTOR_COUNT:
					//存储介质有多少个sector，文件系统通过该值获得存储介质的容量
					*(DWORD *)buff = 16*1024*1024/FLASH_SECTOR_SIZE;
					
					res = RES_OK;
					break;
				
				case GET_SECTOR_SIZE:
					*(WORD *)buff = FLASH_SECTOR_SIZE;
					//每个扇区的个数
				
					res = RES_OK;
					break;
					
				case GET_BLOCK_SIZE:
					*(DWORD *)buff = 1;
					//获取擦除的最小个数，以sector为单位
					
					res = RES_OK;
					break;
				
				case CTRL_SYNC:
					//写入同步在disk_write函数已经完成，这里默认返回ok
					res = RES_OK;
					break;
				
				default:
					res = RES_PARERR;		//参数错位
					break;
			}
			return res;		
	}

	return RES_PARERR;
}
#endif

//获取时间
DWORD get_fattime(void)
{
	
	return 0;
}

