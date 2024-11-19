#ifndef __ESP8266_H
#define __ESP8266_H
#include "sys.h"

extern unsigned char ESP8266_ConnectSta;	    		//-- wifi����״̬
extern unsigned char ESP8266_SendNum;							//-- num��ӦATָ��
extern unsigned char ESP8266_SendTime; 	    			//-- AT ָ���ʱ����
extern unsigned char ESP8266_SendFlag;						//-- wifi�ϴ�����
extern unsigned char ESP8266_UartBuf[50];					//-- ����1wifiͨ��
extern unsigned char ESP8266_UartCount;
extern unsigned char ESP8266_RecKeyValue;
extern unsigned char set;

void ESP8266_Init(void);
void ESP8266_UartReceive(void);
void ESP8266_ConnectServer(void);

#endif

