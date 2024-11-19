#ifndef __ESP8266_H
#define __ESP8266_H
#include "sys.h"

extern unsigned char ESP8266_ConnectSta;	    		//-- wifi连接状态
extern unsigned char ESP8266_SendNum;							//-- num对应AT指令
extern unsigned char ESP8266_SendTime; 	    			//-- AT 指令发送时间间隔
extern unsigned char ESP8266_SendFlag;						//-- wifi上传数据
extern unsigned char ESP8266_UartBuf[50];					//-- 串口1wifi通信
extern unsigned char ESP8266_UartCount;
extern unsigned char ESP8266_RecKeyValue;
extern unsigned char set;

void ESP8266_Init(void);
void ESP8266_UartReceive(void);
void ESP8266_ConnectServer(void);

#endif

