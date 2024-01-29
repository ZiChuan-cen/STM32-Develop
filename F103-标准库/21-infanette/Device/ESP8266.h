#ifndef __ESP8266_H
#define __ESP8266_H
//#include "main.h"

#include "stm32f10x.h"                  // Device header


#define ESP8266_WIFICHOOSE	   1	  //-- ESP8266_WIFICHOOSE  0局域网；1服务器；2云

extern unsigned char ESP8266_UartBuf[50];	//-- 串口1wifi通信
extern unsigned char ESP8266_UartCount;
extern unsigned char ESP8266_RecKeyValue;
extern unsigned char ESP8266_ConnectSta;
extern unsigned char ESP8266_SendNum;
extern uint8_t ESP8266_SendFlag;
extern unsigned char ESP8266_SendTime;
void ESP8266_UartReceive(void);
void ESP8266_ConnectServer(void);



#endif


