#ifndef __HC05_H
#define __HC05_H


#include "stm32f10x.h"





void BlueTooth_Init(void);
void HC05_EnterAT(void);
void HC05_ExitAT(void);
void HC05_SendString(char *Buf);
void HC05_GetData(char *Buf);


#endif  /* __HC05_H */

