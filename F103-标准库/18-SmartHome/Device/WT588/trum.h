#define __TRUM_H	
#ifdef __TRUM_H

#include "sys.h"

#define SDAPort                                 GPIOB
#define SDAPin                                  GPIO_Pin_7
#define CSPort                                  GPIOB
#define CSPin                                   GPIO_Pin_8
#define SCLPort                                 GPIOB
#define SCLPin                                  GPIO_Pin_9

#define SDA_L()                          		GPIO_ResetBits(SDAPort,SDAPin) 
#define SDA_H()                         		GPIO_SetBits(SDAPort,SDAPin)

#define CS_L() 					                GPIO_ResetBits(CSPort,CSPin) 
#define CS_H()                         			GPIO_SetBits(CSPort,CSPin)

#define SCL_L()                          		GPIO_ResetBits(SCLPort,SCLPin) 
#define SCL_H()                              	GPIO_SetBits(SCLPort,SCLPin)

extern uint8_t WT588_Ms;
extern uint8_t WT588_PlaySta;

void Trum_Init(void);
void WT588D_WriteByte(uint8_t addr);
void WT588_Play(unsigned char type,int delay_ms,int dat);

#endif
