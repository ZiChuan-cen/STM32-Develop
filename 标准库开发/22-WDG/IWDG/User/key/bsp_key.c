/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  zichuan
  * @version V1.0
  * @date    2023-06-07
  * @brief   按键驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板
  *
  ******************************************************************************
  */



#include "bsp_key.h"




/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void KEY_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启按键GPIO口的时钟*/
    RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK | KEY2_GPIO_CLK, ENABLE);

    /*选择按键的引脚*/
    GPIO_InitStructure.GPIO_Pin = KEY1_PIN;

    /*设置引脚为输入模式*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;

    /*设置引脚不上拉也不下拉*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    /*使用上面的结构体初始化按键*/
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);

    /*选择按键的引脚*/
    GPIO_InitStructure.GPIO_Pin = KEY2_PIN;

    /*使用上面的结构体初始化按键*/
    GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);

}


/**
  * @brief   检测是否有按键按下
  * @param   GPIOx:具体的端口, x可以是（A...K）
  * @param   GPIO_PIN:具体的端口位，可以是GPIO_PIN_x（x可以是0...15）
  * @retval  按键的状态
  * @arg     KEY_ON:按键按下
  * @arg     KEY_OFF:按键没按下
  */
uint8_t KEY_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)   /*检测是否有按键按下 */
    {
        while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON);  /*等待按键释放 */
        return  KEY_ON;
    }
    else
        return KEY_OFF;

}


