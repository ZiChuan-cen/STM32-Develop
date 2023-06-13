#include "bsp_clkconfig.h"

void USER_SetSysClock(void)
{
/******************************************************************************/
/*            PLL (clocked by HSE) used as System clock source                */
/******************************************************************************/
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
	/* ʹ��HSE */
  RCC->CR |= ((uint32_t)RCC_CR_HSEON); 
  
	/* �ȴ�HSE�����ȶ��������ʱ���˳� */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }
	
	/* HSE �����ɹ� */
	
  if (HSEStatus == (uint32_t)0x01)
  {
    
		/* ѡ���ѹ��������ģʽΪ1 */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    /* HCLK = SYSCLK / 1*/
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    /* PCLK2 = HCLK / 2*/
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;    
    /* PCLK1 = HCLK / 4*/
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
    
		/* ������PLL */
//    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
//                   (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);
		
		RCC->PLLCFGR = 25 | (336 << 6) | (((2 >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSE) | (7 << 24);
    
		/* ʹ����TLL */
    RCC->CR |= RCC_CR_PLLON;

		/* �ȴ���PLL�ȶ� */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

		/* ����FLASH��Ԥȡָ��ָ��棬���ݻ��棬�ȴ����� */
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

		/* ѡ����PLLʱ����Ϊϵͳʱ�� */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;

		/* ȷ����PLLʱ��ѡΪϵͳʱ�� */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
			
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
 
}
