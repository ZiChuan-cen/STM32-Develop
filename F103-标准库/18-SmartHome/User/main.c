#include "sys.h"
#include "timer.h"
#include "dht11.h"
#include "io.h"
#include "adc.h"
#include "oled.h"
#include "usart.h"
#include "trum.h"
#include "stmflash.h"
#include "esp8266.h"
#define Temp_H_ADDR		0x08004000
#define Temp_L_ADDR		0x08004002
#define Humi_H_ADDR		0x08004004
#define Humi_L_ADDR		0x08004006
#define Light_L_ADDR	0x08004008
#define Fumes_H_ADDR	0x0800400A

//============================================================= 变量定义
unsigned int Humi,Humi_H,Humi_L;					//湿度阈值	
unsigned int Temp,Temp_H,Temp_L;					//温度阈值
unsigned int Light,Light_L;							//光线阈值
unsigned char Fumes,Fumes_H;						//烟雾阈值
unsigned char BEEP_Flag,Waring_Flag,s0,set;			//			
unsigned char KEY_Value;							//键值
unsigned char People_Flag;							//红外标志
unsigned char AD_Flag;								//AD采集标志							
unsigned char Deployed;								//布防标志


//========================= 温度读取 ============================
void Read_Temp()
{
	DHT11_Data_TypeDef Temp_Data;
	if(DHT11_Read_TempAndHumidity(&Temp_Data)==SUCCESS)
	{   
			Humi=Temp_Data.humidity;
			Temp=Temp_Data.temperature;
	}
}

//============================= 读取存储数值 ================================
void FLASH_Read()	
{
	Temp_H=STMFLASH_ReadHalfWord(Temp_H_ADDR);
	if(Temp_H>99)Temp_H=45;

	Temp_L=STMFLASH_ReadHalfWord(Temp_L_ADDR);
	if(Temp_L>99)Temp_L=10;
	
	Humi_H=STMFLASH_ReadHalfWord(Humi_H_ADDR);
	if(Humi_H>99)Humi_H=75;

	Humi_L=STMFLASH_ReadHalfWord(Humi_L_ADDR);
	if(Humi_L>99)Humi_L=10;
	
	Light_L=STMFLASH_ReadHalfWord(Light_L_ADDR);
	if(Light_L>99)Light_L=20;
	
	Fumes_H=STMFLASH_ReadHalfWord(Fumes_H_ADDR);
	if(Fumes_H>99)Fumes_H=20;
	
	
	
}

//============================= 写入数据 ===================================
void FLASH_Write()		
{
	if(set==0)
	{							
		u16_Write(Temp_H_ADDR,Temp_H);
		u16_Write(Temp_L_ADDR,Temp_L);
		u16_Write(Humi_H_ADDR,Humi_H);
		u16_Write(Humi_L_ADDR,Humi_L);
		u16_Write(Light_L_ADDR,Light_L);
		u16_Write(Fumes_H_ADDR,Fumes_H);
	}
}




//============================= 超限报警 ===================================
void Warning()		
{
	if(Temp>Temp_H||Temp<Temp_L||Humi<Humi_L||Humi>Humi_H||Light<Light_L||Fumes>Fumes_H)	BEEP_Flag=1;		
	else 																					BEEP_Flag=0;
	
	if(Deployed&&People_Flag)Waring_Flag=1;				//开启布防才会红外报警
	else					 Waring_Flag=0;
		
}


//============================= 按键设置 =================================
void KEY_Read()		
{		
		KEY_Value=key_scan();						//矩阵键盘
		switch(KEY_Value)
		{
			case 1:
				set=(set+1)%7;
				FLASH_Write();
				break;
			case 2:
				switch(set)
				{
					case 0:
						Deployed=1-Deployed;	//布防
						break;
					case 1:
						if(Temp_H<99) 			Temp_H++;
						break;
					case 2:
						if(Temp_L+1<Temp_H) 	Temp_L++;
						break;
					case 3:
						if(Humi_H<99) 			Humi_H++;
						break;
					case 4:
						if(Humi_L+1<Humi_H) 	Humi_L++;
						break;
					case 5:
						if(Light_L<99) 			Light_L++;
						break;
					case 6:
						if(Fumes_H<99) 			Fumes_H++;
						break;
				}
				break;
			case 3:
				switch(set)
				{
					case 0:
						WT588_Play(0,15,0);
						break;
					case 1:
						if(Temp_H>Temp_L+1) 	Temp_H--;
						break;
					case 2:
						if(Temp_L>0) 			Temp_L--;
						break;
					case 3:
						if(Humi_H>Humi_L+1) 	Humi_H--;
						break;
					case 4:
						if(Humi_L>1) 			Humi_L--;
						break;
					case 5:
						if(Light_L>1) 			Light_L--;
						break;
					case 6:
						if(Fumes_H>1) 			Fumes_H--;
						break;
				}
				break;
			case 4:
				WT588_Play(0,15,1);			//播放音乐
				break;
					

		}
		
			
}


//============================== 数据显示及设置页面 ====================================
void OLED_Disp()
{
				
		
		display_GB2312_string(0,0," IR:");	
		if(People_Flag==0)display_GB2312_string(0,4," NO");
		else			  display_GB2312_string(0,4,"YES");
		display_GB2312_string(0,9," L:");
		if(Light>99)Display_Byte(0,12,Light/100%10);
		else display_GB2312_string(0,12," ");
		if(Light>9)Display_Byte(0,13,Light/10%10);
		else display_GB2312_string(0,13," ");
		Display_Byte(0,14,Light%10);
		display_GB2312_string(0,15,"%");
			
		Display_Byte(1,1,Temp/10%10);
		Display_Byte(1,2,Temp%10);
		display_GB2312_string(1,3,"°");	
		
		Display_Byte(1,5,Humi/10%10);
		Display_Byte(1,6,Humi%10);
		display_GB2312_string(1,7,"%");	
	
		display_GB2312_string(1,9," F:");
		if(Fumes>99)Display_Byte(1,12,Fumes/100%10);
		else display_GB2312_string(1,12," ");
		if(Fumes>9)Display_Byte(1,13,Fumes/10%10);
		else display_GB2312_string(1,13," ");
		Display_Byte(1,14,Fumes%10);
		
		display_GB2312_string(1,15,"%");	
	if(set==0)
	{
		display_GB2312_string(2,0," TH:");	
		Display_Byte(2 , 4, Temp_H/10%10);
		Display_Byte(2 , 5, Temp_H/1%10);
		display_GB2312_string(2,6,"°  ");
		display_GB2312_string(2,10,"TL:");	
		Display_Byte(2 , 13, Temp_L/10%10);
		Display_Byte(2 , 14, Temp_L/1%10);
		display_GB2312_string(2,15,"°");
		
		display_GB2312_string(3,0," HH:");	
		Display_Byte(3 , 4, Humi_H/10%10);
		Display_Byte(3 , 5, Humi_H/1%10);
		display_GB2312_string(3,6,"%   ");
		display_GB2312_string(3,10,"HL:");	
		Display_Byte(3 , 13, Humi_L/10%10);
		Display_Byte(3 , 14, Humi_L/1%10);
		display_GB2312_string(3,15,"%  ");
	}
	else if(set<5)
	{		
		if(set==1 && s0==1) display_GB2312_string(2,0," TH:  ");	
		else
		{
			display_GB2312_string(2,0," TH:");	
			Display_Byte(2 , 4, Temp_H/10%10);
			Display_Byte(2 , 5, Temp_H/1%10);
				
		}
		display_GB2312_string(2,6,"°  ");
		if(set==2 && s0==1) display_GB2312_string(2,10,"TL:  ");	
		else
		{
			display_GB2312_string(2,10,"TL:");	
			Display_Byte(2 , 13, Temp_L/10%10);
			Display_Byte(2 , 14, Temp_L/1%10);
				
		}
		display_GB2312_string(2,15,"°");
		if(set==3 && s0==1) display_GB2312_string(3,0," HH:  ");	
		else
		{
			display_GB2312_string(3,0," HH:");	
			Display_Byte(3 , 4, Humi_H/10%10);
			Display_Byte(3 , 5, Humi_H/1%10);
			
		}
		display_GB2312_string(3,6,"%   ");
		if(set==4 && s0==1) display_GB2312_string(3,10,"HL:  ");	
		else
		{
			display_GB2312_string(3,10,"HL:");	
			Display_Byte(3 , 13, Humi_L/10%10);
			Display_Byte(3 , 14, Humi_L/1%10);
			
		}
		display_GB2312_string(3,15,"%  ");	
	}
	else
	{
		if(set==5 && s0==1) display_GB2312_string(2,0," Light_L:  ");	
		else
		{
			display_GB2312_string(2,0," Light_L:");	
			Display_Byte(2 , 9, Light_L/10%10);
			Display_Byte(2 , 10, Light_L/1%10);
			
		}
		display_GB2312_string(2,11,"%      ");
		if(set==6 && s0==1) display_GB2312_string(3,0," Fumes_H:  ");	
		else
		{
			display_GB2312_string(3,0," Fumes_H:");	
			Display_Byte(3 , 9, Fumes_H/10%10);
			Display_Byte(3 , 10, Fumes_H/1%10);
		}
		display_GB2312_string(3,11,"%      ");

		
	}
}


//================================== 烟雾检测 =======================================
void AD_Data()
{
	float temp1,temp2;
	if(AD_Flag==1)
	{
		AD_Flag=0;
		temp1=Get_Value(ADC_Channel_8);
		temp2=Get_Value(ADC_Channel_9);
		
		Light= temp1/4095 *100;
		if(temp2<5)Fumes=0;
		else Fumes= (temp2-5)/2550*100;
	}

}


//================================ 红外检测 =========================================
void Check()
{
	if(IR==0)People_Flag=1;
	else 	 People_Flag=0;
}

//=================================== 发送数据 =========================================
void ESP8266_UartSendData()
{

		USART1_SendString("Data,");

		Usart1Send(0x30+Temp/10%10);
		Usart1Send(0x30+Temp%10);
		USART1_SendString(",");
	
		Usart1Send(0x30+Humi/10%10);
		Usart1Send(0x30+Humi%10);
		USART1_SendString(",");
	
		Usart1Send(0x30+Light/100%10);
		Usart1Send(0x30+Light/10%10);
		Usart1Send(0x30+Light%10);
		USART1_SendString(",");
	
		Usart1Send(0x30+Fumes/100%10);
		Usart1Send(0x30+Fumes/10%10);
		Usart1Send(0x30+Fumes%10);
		USART1_SendString(",");

		Usart1Send(0x30+Temp_H/10%10);								
		Usart1Send(0x30+Temp_H%10);
		USART1_SendString(",");

		Usart1Send(0x30+Temp_L/10%10);								
		Usart1Send(0x30+Temp_L%10);
		USART1_SendString(",");

		Usart1Send(0x30+Humi_H/10%10);								
		Usart1Send(0x30+Humi_H%10);
		USART1_SendString(",");

		Usart1Send(0x30+Humi_L/10%10);								
		Usart1Send(0x30+Humi_L%10);
		USART1_SendString(",");
		
		Usart1Send(0x30+Light_L/10%10);								
		Usart1Send(0x30+Light_L%10);
		USART1_SendString(",");

		Usart1Send(0x30+Fumes_H/10%10);								
		Usart1Send(0x30+Fumes_H%10);
		USART1_SendString(",");
		
		Usart1Send(0x30+People_Flag%10);								
		USART1_SendString(",");
		
		Usart1Send(0x30+Deployed%10);			//布防标志								
		USART1_SendString(",");
		
		Usart1Send(0x30+set%10);									
		USART1_SendString(",");
		
		Usart1Send(0x30+BEEP_Flag%10);								
		USART1_SendString(",");
		Usart1Send(0x30+Waring_Flag%10);							
		USART1_SendString(",");

		USART1_SendString("\r\n");


}

//=============================== wifi接收控制 ====================================
void ESP8266_UartReceive()
{
		if(ESP8266_UartBuf[ESP8266_UartCount-7]=='a' && ESP8266_UartBuf[ESP8266_UartCount-6]=='t' && ESP8266_UartBuf[ESP8266_UartCount-5]=='a' && ESP8266_UartBuf[ESP8266_UartCount-4]==':')//data:A
		{
				switch(ESP8266_UartBuf[ESP8266_UartCount-3])
				{
						case 'A':
							set=(set+1)%7;
							FLASH_Write();
							break;
						case 'B':
							switch(set)
							{
								case 0:
									Deployed=1-Deployed;	//布防
									break;
								case 1:
									if(Temp_H<99) 			Temp_H++;
									break;
								case 2:
									if(Temp_L+1<Temp_H) 	Temp_L++;
									break;
								case 3:
									if(Humi_H<99) 			Humi_H++;
									break;
								case 4:
									if(Humi_L+1<Humi_H) 	Humi_L++;
									break;
								case 5:
									if(Light_L<99) 			Light_L++;
									break;
								case 6:
									if(Fumes_H<99) 			Fumes_H++;
									break;
							}
							break;
						case 'C':
							switch(set)
							{
								case 0:
									WT588_Play(0,15,0);
									break;
								case 1:
									if(Temp_H>Temp_L+1) 	Temp_H--;
									break;
								case 2:
									if(Temp_L>0) 			Temp_L--;
									break;
								case 3:
									if(Humi_H>Humi_L+1) 	Humi_H--;
									break;
								case 4:
									if(Humi_L>1) 			Humi_L--;
									break;
								case 5:
									if(Light_L>1) 			Light_L--;
									break;
								case 6:
									if(Fumes_H>1) 			Fumes_H--;
									break;
							}
							break;
						case 'D':
							WT588_Play(0,15,1);
							break;

				}
		}
}






int main(void)
 {	
	 delay_init();
	 IO_Init();							//外设IO初始化
	 TIM3_Init(9999,71);
	 usart1_Init(9600);
	 FLASH_Read();					//读取数据
	 Adc_Init();
	 OLED_Init();
	 Trum_Init();
	 WT588_Play(0,15,0);
	 while(1)
	 {
	  	 Read_Temp();
		 Check();
		 OLED_Disp();
		 AD_Data();
		 Warning();
		 if(ESP8266_SendTime==0) ESP8266_ConnectServer();
	 }
	
 }
 
unsigned int Timer3_ms=0;

//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		Timer3_ms++;
		KEY_Read();
		if(Timer3_ms%5==0)
		{
				if(WT588_Ms!=0)WT588_Ms--;
				AD_Flag=1;	
		}
		
		if(Timer3_ms%25==0)
		{
				if(ESP8266_SendTime!=0)ESP8266_SendTime--;
				s0=1-s0;
				if(BEEP_Flag||Waring_Flag) 			
				{
						BEEP=~BEEP;
						Waring_LED=~Waring_LED;
				}
				else	{BEEP=0;Waring_LED=1;}
				
		}

		if(Timer3_ms>=100)
		{
				if(ESP8266_ConnectSta==2)WiFi_LED=0;
				else WiFi_LED=1;
				Timer3_ms=0;
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志
	}
}





