#include "io.h"
#include "stm32f10x_it.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_pwr.h"


void IO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    WiFi_LED = 1;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//此句非常重要，PB3 JTAG口复用。

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    Waring_LED = 1;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    PWR_BackupAccessCmd(ENABLE);   /* 允许修改RTC和后备寄存器*/
    RCC_LSEConfig(RCC_LSE_OFF);    /* 关闭外部低速时钟,PC14+PC15可以用作普通IO*/
    BKP_TamperPinCmd(DISABLE);     /* 关闭入侵检测功能,PC13可以用作普通IO*/
    //BEEP
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    BKP_ITConfig(DISABLE);
    BEEP = 0;
    PWR_BackupAccessCmd(DISABLE);/* 禁止修改RTC和后备寄存器*/

}

u8 key_scan()
{
    static u8 key_up = 1; //按键按松开标志
    if (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0)
    {
        if (key_up)
        {
            key_up = 0;
            if (KEY1 == 0) return 1;
            else if (KEY2 == 0)return 2;
            else if (KEY3 == 0)return 3;
            else if (KEY4 == 0)return 4;

        }
    }
    else
    {
        key_up = 1;
    }


    return 0;
}



