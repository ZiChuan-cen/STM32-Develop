#include "KEY.h"



uint8_t Keyvalue;





void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}



void Key_Scan(void)
{
    static uint8_t keyflag;
    if (!Key1 || !Key2 || !Key3)
    {
        if (keyflag == 1)
        {
            keyflag = 0;
            if (!Key1)           Keyvalue = 1;
            else if (!Key2)       Keyvalue = 2;
            else if (!Key3)       Keyvalue = 3;
        }
    }
    else keyflag = 1;
}



