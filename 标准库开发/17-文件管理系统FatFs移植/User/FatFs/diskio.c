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

//�����߼��豸��
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
		//SD��״̬���ط�֧		
		return stat;
	case SPI_FLASH :
		//SPI_FLASH״̬���ط�֧
		spi_result = SPI_FLASH_Read_ID();		
		if(spi_result == 0x16)
		{
			stat &= ~STA_NOINIT;		//stat���λΪ0����ʾSPI FLASH Ϊ����״̬
		}
		else
		{
			stat |= STA_NOINIT;		//stat���λΪ1����ʾSPI FLASH Ϊ������״̬
		}
		return stat;
//	case USB :
//		//USB״̬���ط�֧
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
		//SD����ʼ����֧
		return stat;
	case SPI_FLASH :
		//SPI_FLASH��ʼ����֧
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
	case SD_CARD :		//SD��ȡ��֧
		return res;
	
	case SPI_FLASH :		//SPI_FLASH��ȡ��֧		
		SPI_FLASH_Read_Buff((uint8_t*)buff, sector*FLASH_SECTOR_SIZE, count*FLASH_SECTOR_SIZE);
						//sector*FLASH_SECTOR_SIZE;		��Ҫ��ȡ��������ת���ɵ�ַ
	
		return RES_OK;		//Ĭ��ÿ�ζ���������ȡ
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
	case SD_CARD :		//SDд���֧
		return res;
	case SPI_FLASH :	//SPI_FLASHд���֧	
		while(count--)
		{
			SPI_FLASH_Erase_Sector(sector*FLASH_SECTOR_SIZE);		//д��ǰ�Ȳ���
			
			SPI_FLASH_Write_Buff((uint8_t*)buff, sector*FLASH_SECTOR_SIZE, 1*FLASH_SECTOR_SIZE);
					//sector*FLASH_SECTOR_SIZE:��Ҫд���������ת���ɵ�ַ
			sector++;
			buff += FLASH_SECTOR_SIZE;
		}
		return RES_OK;		//Ĭ��ÿ�ζ���������ȡ
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
		case SD_CARD :		//SD��֧
			
			return res;
		case SPI_FLASH :		//SPI_FLASH��֧	
			
			switch(cmd)
			{			
				case GET_SECTOR_COUNT:
					//�洢�����ж��ٸ�sector���ļ�ϵͳͨ����ֵ��ô洢���ʵ�����
					*(DWORD *)buff = 16*1024*1024/FLASH_SECTOR_SIZE;
					
					res = RES_OK;
					break;
				
				case GET_SECTOR_SIZE:
					*(WORD *)buff = FLASH_SECTOR_SIZE;
					//ÿ�������ĸ���
				
					res = RES_OK;
					break;
					
				case GET_BLOCK_SIZE:
					*(DWORD *)buff = 1;
					//��ȡ��������С��������sectorΪ��λ
					
					res = RES_OK;
					break;
				
				case CTRL_SYNC:
					//д��ͬ����disk_write�����Ѿ���ɣ�����Ĭ�Ϸ���ok
					res = RES_OK;
					break;
				
				default:
					res = RES_PARERR;		//������λ
					break;
			}
			return res;		
	}

	return RES_PARERR;
}
#endif

//��ȡʱ��
DWORD get_fattime(void)
{
	
	return 0;
}

