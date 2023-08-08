/**
  ******************************************************************************
  * @file    main.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-13
  * @brief   主函数
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "delay.h"
#include "OLED.h"
#include "ESP.h"
#include "MQTT.h"


void Init(void)
{
    uint8_t Judge = 0;
    OLED_Init();
    OLED_ShowString(1, 1, "Linking...");
    ESP_GPIO_Init(); //初始化串口

    do
    {
        Judge = esp_Init();
        OLED_ShowString(1, 1, "error code:    ");
        OLED_ShowNum(2, 1, Judge, 1);
    }
    while (Judge);  //连接阿里云直到成功



}



int main(void)
{

    OLED_Init();


    OLED_ShowChar(1, 1, 'A');

    Delay_ms(2000);

    Init();

    while (1)
    {



    }
}

