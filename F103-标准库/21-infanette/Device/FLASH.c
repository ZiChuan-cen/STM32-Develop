#include "FLASH.h"


//flash地址起始于0x0800 0000，
//结束地址是0x0800 0000 + 芯片实际的flash大小
//不同的芯片flash大小不同

//一般用来存储代码和一些定义为const的数据，断电不丢失

void Write_flsh_byte(uint32_t EEPROM_ADD, uint32_t EEPROM_Data)
{
    //1、解锁FLASH
    FLASH_Unlock();
    //2、擦除FLASH
    //初始化FLASH_EraseInitTypeDef

//    FLASH_EraseInitTypeDef f;
//    f.TypeErase = FLASH_TYPEERASE_PAGES;
//    f.PageAddress = EEPROM_ADD;
//    f.NbPages = 1;
//    //设置PageError
//    uint32_t PageError = 0;
    //调用擦除函数
    FLASH_ErasePage(EEPROM_ADD);
    //3、对FLASH烧写
    FLASH_ProgramWord(EEPROM_ADD, EEPROM_Data);
    FLASH_Lock();
}

//FLASH读取数据测试
uint32_t readFlash(uint32_t EEPROM_ADD)
{
    uint32_t temp = *(__IO uint32_t *)(EEPROM_ADD);
    return temp;
}







