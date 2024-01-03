#include "Fan.h"

void Fan_Init(void)
{
    /*********************************≈‰÷√GPIO*************************************/
    RCC_APB2PeriphClockCmd(Fan_GPIO_CLK, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    //PA5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //∏¥”√Õ∆ÕÏ ‰≥ˆ
    GPIO_InitStructure.GPIO_Pin  = Fan_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Fan_PORT, &GPIO_InitStructure);//≥ı ºªØºƒ¥Ê∆˜
}


void Fan_ON(void)       //PA5÷√1
{
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
}


void Fan_OFF(void)      //PA5÷√0
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}


