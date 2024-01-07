#include "trum.h"

uint8_t WT588_Ms;
uint8_t WT588_PlaySta=0;
void Turm_delay_us(uint8_t us)
{
    while(us--);
}


void Trum_Init()
{
	
		GPIO_InitTypeDef GPIO_InitStructure;  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		
		GPIO_InitStructure.GPIO_Pin=SDAPin|CSPin|SCLPin;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}



void WT588D_WriteByte(uint8_t addr)
{
    uint8_t i;
    CS_L();
    delay_ms(5);
    for(i=0;i<8;i++)
    {
        SCL_L();
        if(addr&0x01)               SDA_H();
        else                        SDA_L();
        addr>>=1;
        Turm_delay_us(120);
        SCL_H();
        Turm_delay_us(120);
        
    }
    CS_H();
}

void WT588_Play(unsigned char type,int delay_ms,int dat)
{
		int integer=0,decimal=0;
		if(WT588_Ms==0)
		{
				if(type==0)	 {
				WT588D_WriteByte(dat);
				WT588_Ms=delay_ms;}
				else if(type==1||type==2)
				{
						if(type==1)		 {integer=dat;decimal=0;}
						else if(type==2) {integer=dat/10;decimal=dat%10;}
						switch(WT588_PlaySta)
						{
								case 0:
											if(dat<0)				WT588D_WriteByte(10);
											else					{WT588_PlaySta=1;	goto	LOOP1;}				
											WT588_PlaySta++;
											WT588_Ms=delay_ms;
								break;
								case 1:
						LOOP1:				if(integer/1000%10>0)		WT588D_WriteByte(integer/1000%10);	
											else if(integer/1000%10<0) 	WT588D_WriteByte((-integer)/1000%10);							
											else if(integer/1000%10==0)	{WT588_PlaySta=3;	goto	LOOP2;}																
											WT588_PlaySta++;
											WT588_Ms=delay_ms;
								break;
								case 2:
											WT588D_WriteByte(12);
											WT588_PlaySta++;
											WT588_Ms=delay_ms;
								break;
								case 3:
						LOOP2:				if(integer/100%10>0)		WT588D_WriteByte(integer/100%10);
											else if(integer/100%10<0)	WT588D_WriteByte((-integer)/100%10);	
											else if(integer/100%10==0&&integer/1000%10!=0&&(integer/10%10!=0||integer/1%10!=0)) 	 {WT588D_WriteByte(0);WT588_PlaySta=5;WT588_Ms=delay_ms;break;}
											else if(integer/100%10==0&&integer/1000%10!=0&&integer/10%10==0&&integer/1%10==0)		 {WT588_PlaySta=8;break;}					
											else if(integer/100%10==0&&integer/1000%10==0)											 {WT588_PlaySta=5;goto LOOP3;}																						
											WT588_PlaySta++;
											WT588_Ms=delay_ms;
								break;
								case 4:
											WT588D_WriteByte(13);																
											WT588_PlaySta++;
											WT588_Ms=delay_ms;
								break;
								case 5:
						LOOP3:				if(integer/10%10>1)						 	 WT588D_WriteByte(integer/10%10);																	
											else if(integer/10%10<-1) 					 	 WT588D_WriteByte((-integer)/10%10);
											else if(integer/10%10==1&&(integer/1000%10!=0||integer/100%10!=0))						 WT588D_WriteByte(integer/10%10);																	
											else if(integer/10%10==-1&&(integer/1000%10!=0||integer/100%10!=0)) 					 WT588D_WriteByte((-integer)/10%10);
											else if(integer/10%10==1&&integer/1000%10==0&&integer/100%10==0)						 ;																	
											else if(integer/10%10==-1&&integer/1000%10==0&&integer/100%10==0) 					 	 ;
											else if(integer/10%10==0&&integer/100%10!=0&&integer/1%10!=0) 	 					 	 WT588D_WriteByte(0);
											else if(integer/10%10==0&&integer/100%10!=0&&integer/1%10==0) 	 					     {WT588_PlaySta=8;break;}
											else if(integer/10%10==0&&integer/100%10==0) 	 				 					 	 {WT588_PlaySta=7;goto LOOP4;}							
											WT588_PlaySta++;
											WT588_Ms=delay_ms;
								break;
								case 6:
											if(integer/10%10!=0)											 	 				     WT588D_WriteByte(14);														
//											else if(integer/10%10<0) 						  			 	 						 WT588D_WriteByte(14);																									
											WT588_PlaySta++;
											WT588_Ms=delay_ms;
								break;
								case 7:
						LOOP4:				if(integer/1%10>0)												 						 WT588D_WriteByte(integer/1%10);									
											else if(integer/1%10<0)											 						 WT588D_WriteByte((-integer)/1%10);									
											else if(integer/1%10==0&&integer/1000%10==0&&integer/100%10==0&&integer/10%10==0) 		 WT588D_WriteByte(0);																	
											if(decimal!=0) {WT588_PlaySta=8;WT588_Ms=delay_ms;}
											else		   {WT588_PlaySta=10;WT588_Ms=delay_ms;}
								break;
								case 8:	
											if(decimal!=0)  
											{
													WT588D_WriteByte(11);
													WT588_Ms=delay_ms;
													WT588_PlaySta++;
											}else {WT588_PlaySta=10;WT588_Ms=delay_ms;}
								break;
								case 9:	
											if(decimal<0) decimal=-decimal;
											WT588D_WriteByte(decimal);
											WT588_Ms=delay_ms;
											WT588_PlaySta++;
								break;	
						}
                        
						
				}
		}
}
