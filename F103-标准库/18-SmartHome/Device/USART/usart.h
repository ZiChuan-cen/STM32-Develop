#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 


extern uint8_t usart3Rxbuf[512];
extern uint8_t usart3Rxlen;

void usart3_Init(u32 bound);
int Usart3Send(int ch);
void USART3_SendStr(char *Str,int lenth);
void USART3_SendString(char *Str);



extern uint8_t usart1Rxbuf[256];
extern uint8_t usart1Rxlen;
void usart1_Init(u32 bound);
int Usart1Send(int ch);
void USART1_SendStr(char *Str,int lenth);
void USART1_SendString(char *Str);

#endif
