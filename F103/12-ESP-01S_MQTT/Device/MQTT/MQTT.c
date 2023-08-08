#include "MQTT.h"
#include "ESP.h"
#include "delay.h"
#include "OLED.h"
#include <stdio.h>
#include <string.h>





extern char RECS[250];




const char *WIFI = "FAST_6E18";
const char *WIFIASSWORD = "abcd2345.";
const char *ClintID = "STM32-Device|securemode=3,signmethod=hmacsha1,timestamp=789|";
const char *username = "STM32-Device&i3umv5nT1GA";
const char *passwd = "e7e0b0e89bda8e82d5789ac7a25864b940a09fe5";
const char *Url = "i3umv5nT1GA.iot-as-mqtt.cn-shanghai.aliyuncs.com";
const char *pubtopic = "/sys/i3umv5nT1GA/STM32-Device/thing/event/property/post";           //����
const char *subtopic = "/sys/i3umv5nT1GA/STM32-Device/thing/event/property/post_reply";     //����


//func1��func4Ϊ��ƽ̨���豸��ʶ��
const char *func1 = "LED";              //bool
const char *func2 = "Humidity";         //float
const char *func3 = "temperature";      //int




char esp_Init(void)
{
    memset(RECS, 0, sizeof(RECS));
    printf("AT+RST\r\n");  //����
    Delay_ms(2000);

    memset(RECS, 0, sizeof(RECS));
    printf("ATE0\r\n");    //�رջ���
    Delay_ms(1000);
    if (strcmp(RECS, "OK"))
        return 1;

    printf("AT+CWMODE=1\r\n"); //Stationģʽ
    Delay_ms(1000);
    if (strcmp(RECS, "OK"))
        return 2;

    memset(RECS, 0, sizeof(RECS));
    printf("AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI, WIFIASSWORD); //�����ȵ�
    Delay_ms(2000);
    if (strcmp(RECS, "OK"))
        return 3;

    memset(RECS, 0, sizeof(RECS));
    printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n", ClintID, username, passwd); //�û���Ϣ����
    Delay_ms(10);
    if (strcmp(RECS, "OK"))
        return 4;

    memset(RECS, 0, sizeof(RECS));
    printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n", Url); //���ӷ�����
    Delay_ms(1000);
    if (strcmp(RECS, "OK"))
        return 5;

    printf("AT+MQTTSUB=0,\"%s\",1\r\n", subtopic); //������Ϣ
    Delay_ms(500);
    if (strcmp(RECS, "OK"))
        return 5;
    memset(RECS, 0, sizeof(RECS));
    return 0;
}














