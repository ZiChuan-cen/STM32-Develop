int main(void)
{
	while(1){}
} 

/**
  * @brief  简单的延时函数 
  * @param  无
  * @retval 无
  */
void Delay(__IO uint32_t nCount)	
{
	for(; nCount != 0; nCount--);
}
