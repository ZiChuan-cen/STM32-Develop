#include "bsp_usart.h"
#include "ESP8266.h"
#include "usermain.h"


//-------------------------------------------------------------------------------- ESP8266连接
char WifiName[] = "1121";              //-- 如果需要更改WIFI，这里是修改WIFI名称的！
char WifiPassword[] = "88888888";           //-- WIFI 密码
char DeviceID[] = "2024010201";             //-- 存放10位设备ID
unsigned char ESP8266_ConnectSta = 0;       //-- wifi连接状态
unsigned char ESP8266_SendNum = 0;          //-- num对应AT指令
unsigned char ESP8266_SendTime = 0;         //-- AT 指令发送时间间隔
uint8_t ESP8266_SendFlag = 0;                   //-- wifi上传数据


//-------------------------------------------------------------------------------- 接收数据
unsigned char ESP8266_UartBuf[50];  //-- 串口1wifi通信
unsigned char ESP8266_UartCount = 0;
unsigned char ESP8266_RecKeyValue;




#if ESP8266_WIFICHOOSE==0
void ESP8266_ConnectServer(void)
{
    if (ESP8266_ConnectSta == 0)
    {
        ESP8266_SendTime = 5;
        switch (ESP8266_SendNum)
        {
        case  0:
            UartSend_String(1, "AT\r\n");
            break;
        case  1:
            UartSend_String(1, "AT+CWMODE=2\r\n");
            break;
        case  2:
            UartSend_String(1, "AT+CWSAP=\"TendDaDianZi111\",\"123456789\",4,0\r\n");
            ESP8266_SendTime = 10;
            break;
        case  3:
            UartSend_String(1, "AT+CIPMUX=1\r\n");
            ESP8266_SendTime = 10;
            break;
        case  4:
            UartSend_String(1, "AT+CIPSERVER=1,2000\r\n");
            ESP8266_SendTime = 10;
            break;
        case  5:
            ESP8266_ConnectSta = 1;
            ESP8266_SendTime = 0;
            ESP8266_SendNum = 0;
            break;
        default:
            break;
        }
    }
    else if (ESP8266_ConnectSta == 2)
    {
        ESP8266_SendTime = 6;
        switch (ESP8266_SendNum)
        {
        case  0:
            UartSend_String(1, "AT+CIPSEND=0,11\r\n");
            break;
        case  1:
            UartToSend();
            ESP8266_SendNum = 0;
            break;
        default:
            break;
        }
    }
}
#elif ESP8266_WIFICHOOSE==1
void ESP8266_ConnectServer()
{
    if (ESP8266_ConnectSta == 0)
    {
        ESP8266_SendTime = 10;
        switch (ESP8266_SendNum)
        {
        case  0:
            UartSend_String(1, "AT\r\n");
            break;
        case  1:
            UartSend_String(1, "AT+CWMODE=1\r\n");
            break;
        case  2:
            UartSend_String(1, "AT+CWJAP=\"");
            UartSend_String(1, WifiName);
            UartSend_String(1, "\",\"");
            UartSend_String(1, WifiPassword);
            UartSend_String(1, "\"\r\n");
            ESP8266_SendTime = 10;
            break;
        case  3:
            UartSend_String(1, "AT+CIPMUX=0\r\n");
            ESP8266_SendTime = 10;
            break;
        case  4:
            UartSend_String(1, "AT+CIPSTART=\"TCP\",\"119.23.233.107\",80\r\n");
            ESP8266_SendTime = 20;
            break;
        case  5:
            ESP8266_ConnectSta = 1;
            ESP8266_SendTime = 10;
            ESP8266_SendNum = 0;
            break;
        default:
            break;
        }
    }
    else if (ESP8266_ConnectSta == 1)
    {
        ESP8266_SendTime = 6;
        switch (ESP8266_SendNum)
        {
        case  0:
            UartSend_String(1, "AT+CIPSEND=85\r\n");    //20 +数据字节数
            break;
        case  1:
            UartSend_String(1, "upload,");
            UartSend_String(1, DeviceID);
            UartSend_String(1, ",A:");
            UartToSend();
            ESP8266_SendFlag = 0;
            ESP8266_SendNum = 0;
            break;
        default:
            break;
        }
    }
}
#else
char MQTT_UserName[] = "ESP8266&ilrqqdZMw11";
char MQTT_PassWord[] = "584d1c15564fd79460f2a269ab1dc43beb984d88402f9c385abf987df52584de";
char MQTT_ClientID[] = "ilrqqdZMw11.ESP8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1691646600006|";
char MQTT_HostUrl[] = "iot-06z00dmgumh2jxp.mqtt.iothub.aliyuncs.com";
char MQTT_Port[] = "1883";
char MQTT_PropertyPost[] = "/sys/ilrqqdZMw11/ESP8266/thing/event/property/post";
void ESP8266_ConnectServer()
{
    if (ESP8266_ConnectSta == 0)
    {
        ESP8266_SendTime = 10;
        switch (ESP8266_SendNum)
        {
        case  0:
            UartSend_String(1, "AT\r\n");
            break;
        case  1:
            UartSend_String(1, "AT+CWMODE=1\r\n");
            break;
        case  2:
            UartSend_String(1, "AT+CWJAP=\"");
            UartSend_String(1, WifiName);
            UartSend_String(1, "\",\"");
            UartSend_String(1, WifiPassword);
            UartSend_String(1, "\"\r\n");
            ESP8266_SendTime = 100;
            break;
        case  3:
            UartSend_String(1, "AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");                        //-- 配置单连接
            ESP8266_SendTime = 100;
            break;
        case  4:
            UartSend_String(1, "AT+MQTTUSERCFG=0,1,\"NULL\",\"");
            UartSend_String(1, MQTT_UserName);
            UartSend_String(1, "\",\"");
            UartSend_String(1, MQTT_PassWord);
            UartSend_String(1, "\",0,0,\"\"\r\n");
            ESP8266_SendTime = 100;
            break;
        case  5:
            UartSend_String(1, "AT+MQTTCLIENTID=0,\"");
            UartSend_String(1, MQTT_ClientID);
            UartSend_String(1, "\"\r\n");
            ESP8266_SendTime = 200;
            break;
        case  6:
            UartSend_String(1, "AT+MQTTCONN=0,\"");
            UartSend_String(1, MQTT_HostUrl);
            UartSend_String(1, "\",");
            UartSend_String(1, MQTT_Port);
            UartSend_String(1, ",1\r\n");
            ESP8266_SendTime = 50;
            break;
        case  7:
            ESP8266_ConnectSta = 1;
            ESP8266_SendTime = 0;
            ESP8266_SendNum = 0;
            break;
        default:
            break;
        }
    }
    else if (ESP8266_ConnectSta == 1)
    {
        ESP8266_SendTime = 10;
        UartSend_String(1, "AT+MQTTPUB=0,\"");
        UartSend_String(1, MQTT_PropertyPost);
        UartSend_String(1, "\",\"{\\""\"params\\""\":");
        UartToSend();
        UartSend_String(1, "}\",1,0\r\n");
    }
}
#endif




