#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "./TIM/bsp_advance_time.h"
extern __IO uint16_t ChannelPulse;

void Delay( uint32_t count )
{
	for( ; count != 0 ; count--);
}


int main(void)
{	
	
	TIM_PWMOUTPUT_Config();
	
	while(1);

}
	
