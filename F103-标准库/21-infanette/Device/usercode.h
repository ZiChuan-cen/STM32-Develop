#ifndef __USERCODE_H
#define __USERCODE_H




//================================================================================标志位
uint8_t UartFlag;//串口标志位
uint8_t BeepFlag;//蜂鸣器标志位
uint8_t Dht11Flag;//温湿度标志位
uint8_t TempFlag;//温度标志位

//================================================================================数据
uint8_t SysFace, s0;
uint16_t Temp;//温度
uint8_t Humi;//湿度
uint8_t Heart, Spo2; //心率血氧
uint8_t TempState;//1：温度高于上限2:温度低于下限0：正常
uint8_t HumiState;//1：湿度高于上限2:湿度低于下限0：正常
uint8_t HeartState;//1：心率高于上限2:心率低于下限0：正常
uint8_t Spo2State;//1：血氧高于上限2:血氧低于下限0：正常
uint8_t VoiceState;
uint8_t BeepKey;//按键关闭报警
uint8_t Receive3;//串口接收数据
uint8_t ReadMAX30102data = 0;

//================================================================================阈值
uint8_t Temp_H, Temp_L; //温度上下限
uint8_t Humi_H, Humi_L; //湿度上下限
uint8_t Spo2_H, Spo2_L; //血氧上下限
uint8_t Heart_H, Heart_L; //心率上下限

//================================================================================定时
uint8_t Time_MS;//定时器变量
uint8_t BeepTime;//蜂鸣器定时
unsigned int MAX30102Time = 0;      //-- 测量计时
uint8_t VoiceTime;





#endif

