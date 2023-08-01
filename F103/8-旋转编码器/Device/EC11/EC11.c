#include "EC11.h"
#include "stdio.h"
#include "bsp_usart.h"




void TIM4_Init(u16 arr, u16 psc)
{
    /********************** 初始化结构体变量 **********************/
    NVIC_InitTypeDef    NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //使能 TIM4 时钟
    TIM_TimeBaseStructure.TIM_Period = arr;     //定时器周期
    TIM_TimeBaseStructure.TIM_Prescaler = psc;      //预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);      //使能指定的 TIM 中断，允许更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;       //指定抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      //指定子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM4, ENABLE);

}



/**
    * @brief  定时器4中断服务函数
    * @param  无
    * @retval 无
    */
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        Encoder_EC11_Analyze(Encoder_EC11_Scan());

        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIM4更新中断标志
    }

}


/**
    * @brief  初始化EC11旋转编码器相关参数
    * @param  无
    * @retval 对EC11旋转编码器的连接IO口做IO口模式设置；以及将相关的变量进行初始化
    */
void EC11_Init(unsigned char Set_EC11_TYPE)
{
    GPIO_InitTypeDef    GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
	
	if(Set_EC11_TYPE == 0)
	{
		EC11_Type = 0;
	}else{
		EC11_Type = 1;
	}
	
	//避免上电时EC11旋钮位置不确定导致一次动作误判
	EC11_A_Last = EC11_A_Now;
	EC11_B_Last = EC11_B_Now;
	
	//标志位清零
	EC11_KEY_COUNT = 0;
	EC11_KEY_DoubleClick_Count = 0;
	FLAG_EC11_KEY_ShotClick = 0;
	FLAG_EC11_KEY_LongClick = 0;
	FLAG_EC11_KEY_DoubleClick = 0;
	
	
	TIM4_Init(9, 7199);		//初始化 TIM4 1ms中断
    
}



char Encoder_EC11_Analyze(char EC11_Value)
{
	char AnalyzeResult = 0;
	static unsigned int TMP_Value = 0;		 //中间计数值，用于连续长按按键的动作延时间隔
	
	/************************* 编码器正转处理程序 *************************/
	if(EC11_Value == 1) 	//正转
	{
	  /************************* 正转动作代码 *************************/
		printf("正转！！");
	}
	
	
	/************************* 编码器反转处理程序 *************************/
	if(EC11_Value == 8)    //反转
	{
	  /************************* 反转动作代码 *************************/
		printf("反转！！");
	}

	
	/************************* 编码器按键按下并正转处理程序 *************************/
	if(EC11_Value == 3)
	{
		/************************* 编码器按键按下并正转动作代码 *************************/
			
	}

	
	/************************* 编码器按键按下并反转处理程序 *************************/
	if(EC11_Value == 9)
	{
		/************************* 按键按下并反转动作代码 *************************/
		printf("按下反转！！");
	}
	
	
	/************************* 编码器按键按下处理程序 *************************/
	if(EC11_Value == 2)
	{
		if(EC11_KEY_COUNT < 10000)
			EC11_KEY_COUNT++;
		if(EC11_KEY_COUNT == KEY_COUNT_DESHAKING)	//按下按键时间到达消抖时间时
		{                                           //置位短按按键标志
			FLAG_EC11_KEY_ShotClick = 1;	
		}
		if((EC11_KEY_DoubleClick_Count > 0)&&(EC11_KEY_DoubleClick_Count <= KEY_COUNT_DUALCLICKTIME))   //松开按键后，又在定时器在双击时间内按下按键
		{                                                                                               //置位双击按键标志
			FLAG_EC11_KEY_DoubleClick = 1;
		}

		if(EC11_KEY_COUNT == KEY_COUNT_LONGTIME)    //按下按键时间到达长按时间
		{                                           //置位长按按键标志并复位短按按键标志
			FLAG_EC11_KEY_LongClick = 1;
			FLAG_EC11_KEY_ShotClick = 0;
		}
	}
	else                    //====检测到按键松开====//     
	{
		if(EC11_KEY_COUNT < KEY_COUNT_DESHAKING)    //没到消抖时长就松开按键，复位所有定时器和按键标志
		{	
			EC11_KEY_COUNT = 0;
			FLAG_EC11_KEY_ShotClick = 0;
			FLAG_EC11_KEY_LongClick = 0;
			FLAG_EC11_KEY_DoubleClick = 0;
			EC11_KEY_DoubleClick_Count = 0;
		}
    else
    {     
			if(FLAG_EC11_KEY_ShotClick == 1)        //短按按键定时有效期间
      {
				if((FLAG_EC11_KEY_DoubleClick == 0)&&(EC11_KEY_DoubleClick_Count >= 0)) 
						EC11_KEY_DoubleClick_Count++;
				if((FLAG_EC11_KEY_DoubleClick == 1)&&(EC11_KEY_DoubleClick_Count <= KEY_COUNT_DUALCLICKTIME))   //如果在规定双击时间内再次按下按键
        {                                                                                               //认为按键是双击动作
					FLAG_EC11_KEY_DoubleClick = 2;
        }   
        if((FLAG_EC11_KEY_DoubleClick == 0)&&(EC11_KEY_DoubleClick_Count > KEY_COUNT_DUALCLICKTIME))    //如果没有在规定双击时间内再次按下按键
            FLAG_EC11_KEY_ShotClick = 0;                                                                //认为按键是单击动作
       }
       if(FLAG_EC11_KEY_LongClick == 1)        //检测到长按按键松开
			 {
        FLAG_EC11_KEY_LongClick = 0;
			 }
     }
	}
    //>>>>>>>>>>>>>>>>编码器按键分析处理程序<<<<<<<<<<<<<<<<//
	
	if(EC11_KEY_COUNT > KEY_COUNT_DESHAKING)    //短按按键延时到了时间
	{
		//短按按键动作结束代码
		if((FLAG_EC11_KEY_ShotClick == 0)&&(EC11_KEY_DoubleClick_Count > KEY_COUNT_DUALCLICKTIME)&&(EC11_KEY_COUNT < KEY_COUNT_LONGTIME))   //短按按键动作结束代码
    {
      //--------短按按键动作结束代码--------//
			EC11_NUM_SW++;
			if(EC11_NUM_SW >= 4)
				 EC11_NUM_SW = 1;
			AnalyzeResult = 1;
			
			//--------清除标志位--------//
			EC11_KEY_COUNT = 0;
			EC11_KEY_DoubleClick_Count = 0;
			FLAG_EC11_KEY_DoubleClick = 0;
		}
    //双击按键动作结束代码
		if((FLAG_EC11_KEY_DoubleClick == 2)&&(EC11_KEY_DoubleClick_Count > 0)&&(EC11_KEY_DoubleClick_Count <= KEY_COUNT_DUALCLICKTIME)) //双击按键动作结束代码
    {
			//--------双击按键动作结束代码--------//
			if(EC11_NUM_SW == 5)
				 EC11_NUM_SW = 0;
			if(EC11_NUM_SW == 4)
				 EC11_NUM_SW = 5;
			if(EC11_NUM_SW <4)
			{
				EC11_NUM_SW = 4;
			}
			AnalyzeResult = 2;
			//--------清除标志位--------//
			EC11_KEY_COUNT = 0;
			EC11_KEY_DoubleClick_Count = 0;
			FLAG_EC11_KEY_ShotClick = 0;
			FLAG_EC11_KEY_DoubleClick = 0;    
		}

		//连续长按按键按下代码
		if((FLAG_EC11_KEY_LongClick == 1)&&(EC11_KEY_COUNT >= KEY_COUNT_LONGTIME))  //连续长按按键按下代码
    {
			TMP_Value ++;
			if(TMP_Value % KEY_LONG_REPEAT_TIME == 0)
			{
				TMP_Value = 0;
				//-------连续长按按键按下代码--------//
				AnalyzeResult = 4;
			}
		}

		//长按按键动作结束代码
		if((FLAG_EC11_KEY_LongClick == 0)&&(EC11_KEY_COUNT >= KEY_COUNT_LONGTIME))  //长按按键动作结束代码
		{                                                                           
			//--------长按按键按下动作结束代码--------//
			EC11_NUM_SW = 0;
			AnalyzeResult = 3;
			//--------清除标志位--------//
			EC11_KEY_COUNT = 0;
		}
	}
	return AnalyzeResult;
}

//*******************************************************************/
//功能：扫描EC11旋转编码器的动作并将参数返回给动作分析函数使用
//形参：EC11旋转编码器的类型-->>  unsigned char Set_EC11_TYPE  <<--  ：0----一定位对应一脉冲；1（或非0）----两定位对应一脉冲
//返回：EC11旋转编码器的扫描结果-->>  char ScanResult  -->>  0：无动作；1：正转； -1：反转；2：只按下按键；3：按着按键正转；-3：按着按键反转
//详解：只扫描EC11旋转编码器有没有动作，不关心是第几次按下按键或长按或双击。返回值直接作为形参传给 [ void Encoder_EC11_Analyze(char EC11_Value); ] 函数使用
//*******************************************************************/
char Encoder_EC11_Scan()
{
		//以下储存A、B上一次值的变量声明为静态全局变量，方便对EC11对应的IO口做初始化
		//  static char EC11_A_Last = 0;
		//  static char EC11_B_Last = 0;
	char ScanResult = 0;    //返回编码器扫描结果，用于分析编码器的动作
                          //返回值的取值：   0：无动作；      1：正转；           8：反转；  
                          //                 2：只按下按键；  3：按着按键正转；   9：按着按键反转
                          //======================================================//
	if(EC11_Type == 0)      //================一定位对应一脉冲的EC11================//
	{                     	//======================================================//
		if(EC11_A_Now != EC11_A_Last)   //以A为时钟，B为数据。正转时AB反相，反转时AB同相
		{
			if(EC11_A_Now == 0)
			{
				if(EC11_B_Now ==1)      //只需要采集A的上升沿或下降沿的任意一个状态，若A下降沿时B为1，正转                    
					 ScanResult = 1;     //正转
				else                    //反转
					 ScanResult = 8;
			}
			EC11_A_Last = EC11_A_Now;   //更新编码器上一个状态暂存变量
			EC11_B_Last = EC11_B_Now;   //更新编码器上一个状态暂存变量
		}
	}   
                          //======================================================//
	else                    //================两定位对应一脉冲的EC11================//
	{                       //======================================================//
		if(EC11_A_Now !=EC11_A_Last)        //当A发生跳变时采集B当前的状态，并将B与上一次的状态进行对比。
		{                                   //若A 0->1 时，B 1->0 正转；若A 1->0 时，B 0->1 正转；
                                        //若A 0->1 时，B 0->1 反转；若A 1->0 时，B 1->0 反转
			if(EC11_A_Now == 1)     					//EC11_A和上一次状态相比，为上升沿
			{
				if((EC11_B_Last == 1)&&(EC11_B_Now == 0))   //EC11_B和上一次状态相比，为下降沿
						ScanResult = 1;                         //正转
        if((EC11_B_Last == 0)&&(EC11_B_Now == 1))   //EC11_B和上一次状态相比，为上升沿               
            ScanResult = 8;                        //反转
                //>>>>>>>>>>>>>>>>下面为正转一次再反转或反转一次再正转处理<<<<<<<<<<<<<<<<//
        if((EC11_B_Last == EC11_B_Now)&&(EC11_B_Now == 0))  //A上升沿时，采集的B不变且为0
            ScanResult = 1;                                 //正转
        if((EC11_B_Last == EC11_B_Now)&&(EC11_B_Now == 1))  //A上升沿时，采集的B不变且为1
            ScanResult = 8;                                 //反转
			}
			else                    //EC11_A和上一次状态相比，为下降沿
			{
				if((EC11_B_Last == 1)&&(EC11_B_Now == 0))   //EC11_B和上一次状态相比，为下降沿
						ScanResult = 8;                        //反转
				if((EC11_B_Last == 0)&&(EC11_B_Now == 1))   //EC11_B和上一次状态相比，为上升沿
						ScanResult = 1;                         //正转
				//>>>>>>>>>>>>>>>>下面为正转一次再反转或反转一次再正转处理<<<<<<<<<<<<<<<<//
				if((EC11_B_Last == EC11_B_Now)&&(EC11_B_Now == 0))  //A上升沿时，采集的B不变且为0
						ScanResult = 8;                                //反转
				if((EC11_B_Last == EC11_B_Now)&&(EC11_B_Now == 1))  //A上升沿时，采集的B不变且为1   
						ScanResult = 1;                                 //正转
			}               
				EC11_A_Last = EC11_A_Now;   //更新编码器上一个状态暂存变量
				EC11_B_Last = EC11_B_Now;   //更新编码器上一个状态暂存变量
		}
	}                                                                       
	if(EC11_Key == 0)   //如果EC11的按键按下，并且没有EC11没有转动，
	{
//		if(ScanResult == 0)         //按下按键时未转动
			 ScanResult = 2;         //返回值为2
//		else
//		{
//			if(ScanResult == 1)     //按下按键时候正转
//				 ScanResult = 3;     //返回值为3
//			if(ScanResult == 8)    //按下按键时候反转
//				 ScanResult = 9;    //返回值为-3
//		}
	}
    return ScanResult;      //返回值的取值：   0：无动作；      1：正转；           8：反转；
}                           //             		 2：只按下按键；  3：按着按键正转；   9：按着按键反转












