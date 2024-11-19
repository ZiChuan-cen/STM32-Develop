#include "esp8266.h"
#include "usart.h"


//-------------------------------------------------------------------------------- ESP8266����
char WifiName[] = "wlw2003";                          //-- �����Ҫ����WIFI���������޸�WIFI���Ƶģ�
char WifiPassword[] = "88888888";                       //-- WIFI ����
char DeviceID[] = "2023101702";                         //-- ���10λ�豸ID
unsigned char ESP8266_ConnectSta = 0;                   //-- wifi����״̬
unsigned char ESP8266_SendNum = 0;                      //-- num��ӦATָ��
unsigned char ESP8266_SendTime = 0;                     //-- AT ָ���ʱ����
unsigned char ESP8266_SendFlag = 0;                     //-- wifi�ϴ�����
//-------------------------------------------------------------------------------- ��������
unsigned char  ESP8266_UartBuf[50];                     //-- ����1wifiͨ��
unsigned char ESP8266_UartCount = 0;
unsigned char ESP8266_RecKeyValue;

void ESP8266_UartSendData(void);

/********************************************************************
* ���� : ESP8266_Init(void)
* ���� : ESP8266��ʼ��
* ���� : ��
* ��� : ��
***********************************************************************/

void ESP8266_Init(void)
{
  usart3_Init(9600);
}


//�ȵ����
//void ESP8266_UartReceive()
//{
//      if(ESP8266_UartBuf[ESP8266_UartCount-7]=='a' && ESP8266_UartBuf[ESP8266_UartCount-6]=='t' && ESP8266_UartBuf[ESP8266_UartCount-5]=='a' && ESP8266_UartBuf[ESP8266_UartCount-4]==':')//data:A
//      {
//              switch(ESP8266_UartBuf[ESP8266_UartCount-3])
//              {
//                      case 'A':   ESP8266_RecKeyValue=1;break;
//                      case 'B':   ESP8266_RecKeyValue=2;break;
//                      case 'C':   ESP8266_RecKeyValue=3;break;
//                      case 'D':   ESP8266_RecKeyValue=4;break;
//              }
//      }
//}




/*-----------------------------------�ȵ�����---------------------------------------------*/
void ESP8266_ConnectServer(void)
{
  if (ESP8266_ConnectSta == 0)
    {
      ESP8266_SendTime = 5;
      switch (ESP8266_SendNum)
        {
        case  0:
          USART1_SendString("AT\r\n");
          break;
        case  1:
          USART1_SendString("AT+CWMODE=2\r\n");
          break;
        case  2:
          USART1_SendString("AT+CWSAP=\"TendDaDianZi\",\"123456789\",4,0\r\n");
          ESP8266_SendTime = 10;
          break;
        case  3:
          USART1_SendString("AT+CIPMUX=1\r\n");
          ESP8266_SendTime = 10;
          break;
        case  4:
          USART1_SendString("AT+CIPSERVER=1,2000\r\n");
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
          USART1_SendString("AT+CIPSEND=0,49\r\n");
          break;
        case  1:
          ESP8266_UartSendData();
          ESP8266_SendNum = 0;
          break;
        default:
          break;
        }
    }
}


/*-----------------------------------------TCP ����������-------------------------------------------------*/
/**
//void ESP8266_ConnectServer()
//{
//      if(ESP8266_ConnectSta==0)
//      {
//              ESP8266_SendTime=10;
//              switch(ESP8266_SendNum)
//              {
//                      case  0:USART3_SendString("AT\r\n");            break;
//                      case  1:USART3_SendString("AT+CWMODE=1\r\n");   break;
//                      case  2:
//                              USART3_SendString("AT+CWJAP=\"");
//                              USART3_SendString(WifiName);
//                              USART3_SendString("\",\"");
//                              USART3_SendString(WifiPassword);
//                              USART3_SendString("\"\r\n");
//                              ESP8266_SendTime=10;
//                              break;
//                      case  3:USART3_SendString("AT+CIPMUX=0\r\n");
//                              ESP8266_SendTime=10;
//                              break;
//                      case  4:
//                              USART3_SendString("AT+CIPSTART=\"TCP\",\"119.23.233.107\",80\r\n");
//                              ESP8266_SendTime=20;
//                              break;
//                      case  5:
//                              ESP8266_ConnectSta=1;
//                              ESP8266_SendTime=10;
//                              ESP8266_SendNum=0;
//                              break;
//                      default:break;
//              }
//      }else if(ESP8266_ConnectSta==1)
//      {
//              ESP8266_SendTime=6;
//              switch(ESP8266_SendNum)
//              {
//                      case  0:
//                              USART3_SendString("AT+CIPSEND=57\r\n");     //20 +�����ֽ���
//                              break;
//                      case  1:
//                              USART3_SendString("upload,");
//                              USART3_SendString(DeviceID);
//                              USART3_SendString(",A:");
//                              ESP8266_UartSendData();
//                              ESP8266_SendFlag=0;
//                              ESP8266_SendNum=0;
//                              break;
//                      default:break;
//              }
//      }
//}
**/



/*-----------------------------------------�����Ʒ���������----------------------------------------------------*/
/**
//char  MQTT_UserName[]= "ESP8266&ilrqqdZMw11";
//char  MQTT_PassWord[]= "584d1c15564fd79460f2a269ab1dc43beb984d88402f9c385abf987df52584de";
//char  MQTT_ClientID[]= "ilrqqdZMw11.ESP8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1691646600006|";
//char  MQTT_HostUrl[]= "iot-06z00dmgumh2jxp.mqtt.iothub.aliyuncs.com";
//char  MQTT_Port[]= "1883";
//char  MQTT_PropertyPost[]= "/sys/ilrqqdZMw11/ESP8266/thing/event/property/post";
//void ESP8266_ConnectServer()
//{
//      if(ESP8266_ConnectSta==0)
//      {
//              ESP8266_SendTime=10;
//              switch(ESP8266_SendNum)
//              {
//                      case  0:USART3_SendString("AT\r\n");            break;
//                      case  1:USART3_SendString("AT+CWMODE=1\r\n");   break;
//                      case  2:
//                              USART3_SendString("AT+CWJAP=\"");
//                              USART3_SendString(WifiName);
//                              USART3_SendString("\",\"");
//                              USART3_SendString(WifiPassword);
//                              USART3_SendString("\"\r\n");
//                              ESP8266_SendTime=100;
//                              break;
//                      case  3:USART3_SendString("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");                         //-- ���õ�����
//                              ESP8266_SendTime=100;
//                              break;
//                      case  4:
//                              USART3_SendString("AT+MQTTUSERCFG=0,1,\"NULL\",\"");
//                              USART3_SendString(MQTT_UserName);
//                              USART3_SendString("\",\"");
//                              USART3_SendString(MQTT_PassWord);
//                              USART3_SendString("\",0,0,\"\"\r\n");
//                              ESP8266_SendTime=100;
//                              break;
//                      case  5:
//                              USART3_SendString("AT+MQTTCLIENTID=0,\"");
//                              USART3_SendString(MQTT_ClientID);
//                              USART3_SendString("\"\r\n");
//                              ESP8266_SendTime=200;
//                              break;
//                      case  6:
//                              USART3_SendString("AT+MQTTCONN=0,\"");
//                              USART3_SendString(MQTT_HostUrl);
//                              USART3_SendString("\",");
//                              USART3_SendString(MQTT_Port);
//                              USART3_SendString(",1\r\n");
//                              ESP8266_SendTime=50;
//                              break;
//                      case  7:
//                              ESP8266_ConnectSta=1;
//                              ESP8266_SendTime=0;
//                              ESP8266_SendNum=0;
//                              break;
//                      default:break;
//              }
//      }else if(ESP8266_ConnectSta==1)
//      {
//              ESP8266_SendTime=10;
//              USART3_SendString("AT+MQTTPUB=0,\"");
//              USART3_SendString(MQTT_PropertyPost);
//              USART3_SendString("\",\"{\\""\"params\\""\":");
//              ESP8266_UartSendData();
//              USART3_SendString("}\",1,0\r\n");
//      }
//}



*/






/********************************************************************
* ���� : Uart1_Isr() interrupt 4
* ���� : ����1�����ж�
* ���� : ��
* ��� : ��
***********************************************************************/
//�ȵ�����ж�
void USART1_IRQHandler(void)
{

  if (USART_GetITStatus(USART1, USART_IT_RXNE)) // �жϱ�־
    {
      ESP8266_UartBuf[ESP8266_UartCount] = USART_ReceiveData(USART1);
      ESP8266_UartCount = (ESP8266_UartCount + 1) % 50;
      if (ESP8266_ConnectSta == 0)
        {
          if (ESP8266_UartCount >= 4 && ESP8266_UartBuf[ESP8266_UartCount - 3] == 'K' && ESP8266_UartBuf[ESP8266_UartCount - 4] == 'O') //-- OK
            {
              ESP8266_SendNum++;
            }
          else if (ESP8266_UartCount >= 7 && ESP8266_UartBuf[ESP8266_UartCount - 3] == 'R' && ESP8266_UartBuf[ESP8266_UartCount - 7] == 'E' && ESP8266_UartBuf[ESP8266_UartCount - 1] == '\n' && ESP8266_UartBuf[ESP8266_UartCount - 2] == '\r') //--ERROR
            {
              ESP8266_SendNum = 0;
            }

        }
      else if (ESP8266_ConnectSta == 1)
        {
          if (ESP8266_UartCount >= 9 && ESP8266_UartBuf[ESP8266_UartCount - 3] == 'T' && ESP8266_UartBuf[ESP8266_UartCount - 9] == 'C')
            {
              ESP8266_ConnectSta = 2;
            }
        }
      else if (ESP8266_ConnectSta == 2)
        {
          if (ESP8266_UartCount >= 38 && ESP8266_UartBuf[ESP8266_UartCount - 33] == 'D' && ESP8266_UartBuf[ESP8266_UartCount - 31] == 'S' && ESP8266_UartBuf[ESP8266_UartCount - 22] == 'D')
            {
              ESP8266_ConnectSta = 1;
              ESP8266_SendNum = 0;
            }
          else if (ESP8266_UartCount >= 2 && ESP8266_UartBuf[ESP8266_UartCount - 1] == '>')
            {
              ESP8266_SendNum++;
            }
          else if (ESP8266_UartCount >= 7 && ESP8266_UartBuf[ESP8266_UartCount - 3] == 'R' && ESP8266_UartBuf[ESP8266_UartCount - 7] == 'E') //--ERROR
            {
              ESP8266_SendNum = 0;
            }
        }
      if (ESP8266_UartCount >= 4 && ESP8266_UartBuf[ESP8266_UartCount - 1] == '\n' && ESP8266_UartBuf[ESP8266_UartCount - 2] == '\r')
        {
          ESP8266_UartReceive();
          if (ESP8266_UartBuf[ESP8266_UartCount - 3] == 'Z')
            {
              ESP8266_SendFlag = 1;
            }
          ESP8266_UartCount = 0;
        }

    }

}


//tcp ������

/********************************************************************
* ���� : ����3�����ж�
* ���� : ��
* ��� : ��
***********************************************************************/
//void USART3_IRQHandler()
//{
//      if(USART_GetITStatus(USART3,USART_IT_RXNE))
//      {

//              ESP8266_UartBuf[ESP8266_UartCount] = USART_ReceiveData(USART3);
//              ESP8266_UartCount = (ESP8266_UartCount+1)%50;
//              if(ESP8266_ConnectSta==0)
//              {
//                      if(ESP8266_UartCount>=4 && ESP8266_UartBuf[ESP8266_UartCount-3]=='K'&&ESP8266_UartBuf[ESP8266_UartCount-4]=='O')
//                      {
//                              ESP8266_SendNum++;
//
//                      }else if(ESP8266_UartCount>=7 && ESP8266_UartBuf[ESP8266_UartCount-3]=='R'&&ESP8266_UartBuf[ESP8266_UartCount-7]=='E')
//                      {
//                              ESP8266_SendNum=0;
//                      }
//
//              }else if(ESP8266_ConnectSta==1)
//              {
//                      if(ESP8266_UartCount>=2 && ESP8266_UartBuf[ESP8266_UartCount-1]=='>')
//                      {
//                              ESP8266_SendNum++;
//                      }else if(ESP8266_UartCount>=7 && ESP8266_UartBuf[ESP8266_UartCount-3]=='R'&&ESP8266_UartBuf[ESP8266_UartCount-7]=='E')
//                      {
//                              ESP8266_ConnectSta=0;
//                              ESP8266_SendNum=0;
//                      }
//              }
//              if(ESP8266_UartCount>=4 && ESP8266_UartBuf[ESP8266_UartCount-1]=='\n'&&ESP8266_UartBuf[ESP8266_UartCount-2]=='\r')
//              {
//
//                      ESP8266_UartReceive();
//                      ESP8266_UartCount=0;
//              }
//      }
//}



//�Ʒ�����
/********************************************************************
* ���� : Uart1_Isr() interrupt 4
* ���� : ����1�����ж�
* ���� : ��
* ��� : ��
***********************************************************************/
//void USART3_IRQHandler()
//{
//      if(USART_GetITStatus(USART3,USART_IT_RXNE))
//      {
//              ESP8266_UartBuf[ESP8266_UartCount] = USART_ReceiveData(USART3);
//              ESP8266_UartCount = (ESP8266_UartCount+1)%50;
//              if(ESP8266_ConnectSta==0)
//              {
//                      if(ESP8266_UartCount>=4 && ESP8266_UartBuf[ESP8266_UartCount-3]=='K'&&ESP8266_UartBuf[ESP8266_UartCount-4]=='O')
//                      {
//                              ESP8266_SendNum++;
//
//                      }else if(ESP8266_UartCount>=7 && ESP8266_UartBuf[ESP8266_UartCount-3]=='R'&&ESP8266_UartBuf[ESP8266_UartCount-7]=='E')
//                      {
//                              ESP8266_SendNum=0;
//                      }
//
//              }
//              if(ESP8266_UartCount>=4 && ESP8266_UartBuf[ESP8266_UartCount-1]=='\n'&&ESP8266_UartBuf[ESP8266_UartCount-2]=='\r')
//              {
//                      ESP8266_UartReceive();
//                      ESP8266_UartCount=0;
//              }
//      }
//}



