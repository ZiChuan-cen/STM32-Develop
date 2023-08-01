#include "EC11.h"
#include "stdio.h"
#include "bsp_usart.h"




void TIM4_Init(u16 arr, u16 psc)
{
    /********************** ��ʼ���ṹ����� **********************/
    NVIC_InitTypeDef    NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);    //ʹ�� TIM4 ʱ��
    TIM_TimeBaseStructure.TIM_Period = arr;     //��ʱ������
    TIM_TimeBaseStructure.TIM_Prescaler = psc;      //Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);      //ʹ��ָ���� TIM �жϣ���������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;       //ָ����ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      //ָ�������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM4, ENABLE);

}



/**
    * @brief  ��ʱ��4�жϷ�����
    * @param  ��
    * @retval ��
    */
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        Encoder_EC11_Analyze(Encoder_EC11_Scan());

        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIM4�����жϱ�־
    }

}


/**
    * @brief  ��ʼ��EC11��ת��������ز���
    * @param  ��
    * @retval ��EC11��ת������������IO����IO��ģʽ���ã��Լ�����صı������г�ʼ��
    */
void EC11_Init(unsigned char Set_EC11_TYPE)
{
    GPIO_InitTypeDef    GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
	
	if(Set_EC11_TYPE == 0)
	{
		EC11_Type = 0;
	}else{
		EC11_Type = 1;
	}
	
	//�����ϵ�ʱEC11��ťλ�ò�ȷ������һ�ζ�������
	EC11_A_Last = EC11_A_Now;
	EC11_B_Last = EC11_B_Now;
	
	//��־λ����
	EC11_KEY_COUNT = 0;
	EC11_KEY_DoubleClick_Count = 0;
	FLAG_EC11_KEY_ShotClick = 0;
	FLAG_EC11_KEY_LongClick = 0;
	FLAG_EC11_KEY_DoubleClick = 0;
	
	
	TIM4_Init(9, 7199);		//��ʼ�� TIM4 1ms�ж�
    
}



char Encoder_EC11_Analyze(char EC11_Value)
{
	char AnalyzeResult = 0;
	static unsigned int TMP_Value = 0;		 //�м����ֵ�������������������Ķ�����ʱ���
	
	/************************* ��������ת������� *************************/
	if(EC11_Value == 1) 	//��ת
	{
	  /************************* ��ת�������� *************************/
		printf("��ת����");
	}
	
	
	/************************* ��������ת������� *************************/
	if(EC11_Value == 8)    //��ת
	{
	  /************************* ��ת�������� *************************/
		printf("��ת����");
	}

	
	/************************* �������������²���ת������� *************************/
	if(EC11_Value == 3)
	{
		/************************* �������������²���ת�������� *************************/
			
	}

	
	/************************* �������������²���ת������� *************************/
	if(EC11_Value == 9)
	{
		/************************* �������²���ת�������� *************************/
		printf("���·�ת����");
	}
	
	
	/************************* �������������´������ *************************/
	if(EC11_Value == 2)
	{
		if(EC11_KEY_COUNT < 10000)
			EC11_KEY_COUNT++;
		if(EC11_KEY_COUNT == KEY_COUNT_DESHAKING)	//���°���ʱ�䵽������ʱ��ʱ
		{                                           //��λ�̰�������־
			FLAG_EC11_KEY_ShotClick = 1;	
		}
		if((EC11_KEY_DoubleClick_Count > 0)&&(EC11_KEY_DoubleClick_Count <= KEY_COUNT_DUALCLICKTIME))   //�ɿ����������ڶ�ʱ����˫��ʱ���ڰ��°���
		{                                                                                               //��λ˫��������־
			FLAG_EC11_KEY_DoubleClick = 1;
		}

		if(EC11_KEY_COUNT == KEY_COUNT_LONGTIME)    //���°���ʱ�䵽�ﳤ��ʱ��
		{                                           //��λ����������־����λ�̰�������־
			FLAG_EC11_KEY_LongClick = 1;
			FLAG_EC11_KEY_ShotClick = 0;
		}
	}
	else                    //====��⵽�����ɿ�====//     
	{
		if(EC11_KEY_COUNT < KEY_COUNT_DESHAKING)    //û������ʱ�����ɿ���������λ���ж�ʱ���Ͱ�����־
		{	
			EC11_KEY_COUNT = 0;
			FLAG_EC11_KEY_ShotClick = 0;
			FLAG_EC11_KEY_LongClick = 0;
			FLAG_EC11_KEY_DoubleClick = 0;
			EC11_KEY_DoubleClick_Count = 0;
		}
    else
    {     
			if(FLAG_EC11_KEY_ShotClick == 1)        //�̰�������ʱ��Ч�ڼ�
      {
				if((FLAG_EC11_KEY_DoubleClick == 0)&&(EC11_KEY_DoubleClick_Count >= 0)) 
						EC11_KEY_DoubleClick_Count++;
				if((FLAG_EC11_KEY_DoubleClick == 1)&&(EC11_KEY_DoubleClick_Count <= KEY_COUNT_DUALCLICKTIME))   //����ڹ涨˫��ʱ�����ٴΰ��°���
        {                                                                                               //��Ϊ������˫������
					FLAG_EC11_KEY_DoubleClick = 2;
        }   
        if((FLAG_EC11_KEY_DoubleClick == 0)&&(EC11_KEY_DoubleClick_Count > KEY_COUNT_DUALCLICKTIME))    //���û���ڹ涨˫��ʱ�����ٴΰ��°���
            FLAG_EC11_KEY_ShotClick = 0;                                                                //��Ϊ�����ǵ�������
       }
       if(FLAG_EC11_KEY_LongClick == 1)        //��⵽���������ɿ�
			 {
        FLAG_EC11_KEY_LongClick = 0;
			 }
     }
	}
    //>>>>>>>>>>>>>>>>���������������������<<<<<<<<<<<<<<<<//
	
	if(EC11_KEY_COUNT > KEY_COUNT_DESHAKING)    //�̰�������ʱ����ʱ��
	{
		//�̰�����������������
		if((FLAG_EC11_KEY_ShotClick == 0)&&(EC11_KEY_DoubleClick_Count > KEY_COUNT_DUALCLICKTIME)&&(EC11_KEY_COUNT < KEY_COUNT_LONGTIME))   //�̰�����������������
    {
      //--------�̰�����������������--------//
			EC11_NUM_SW++;
			if(EC11_NUM_SW >= 4)
				 EC11_NUM_SW = 1;
			AnalyzeResult = 1;
			
			//--------�����־λ--------//
			EC11_KEY_COUNT = 0;
			EC11_KEY_DoubleClick_Count = 0;
			FLAG_EC11_KEY_DoubleClick = 0;
		}
    //˫������������������
		if((FLAG_EC11_KEY_DoubleClick == 2)&&(EC11_KEY_DoubleClick_Count > 0)&&(EC11_KEY_DoubleClick_Count <= KEY_COUNT_DUALCLICKTIME)) //˫������������������
    {
			//--------˫������������������--------//
			if(EC11_NUM_SW == 5)
				 EC11_NUM_SW = 0;
			if(EC11_NUM_SW == 4)
				 EC11_NUM_SW = 5;
			if(EC11_NUM_SW <4)
			{
				EC11_NUM_SW = 4;
			}
			AnalyzeResult = 2;
			//--------�����־λ--------//
			EC11_KEY_COUNT = 0;
			EC11_KEY_DoubleClick_Count = 0;
			FLAG_EC11_KEY_ShotClick = 0;
			FLAG_EC11_KEY_DoubleClick = 0;    
		}

		//���������������´���
		if((FLAG_EC11_KEY_LongClick == 1)&&(EC11_KEY_COUNT >= KEY_COUNT_LONGTIME))  //���������������´���
    {
			TMP_Value ++;
			if(TMP_Value % KEY_LONG_REPEAT_TIME == 0)
			{
				TMP_Value = 0;
				//-------���������������´���--------//
				AnalyzeResult = 4;
			}
		}

		//��������������������
		if((FLAG_EC11_KEY_LongClick == 0)&&(EC11_KEY_COUNT >= KEY_COUNT_LONGTIME))  //��������������������
		{                                                                           
			//--------�����������¶�����������--------//
			EC11_NUM_SW = 0;
			AnalyzeResult = 3;
			//--------�����־λ--------//
			EC11_KEY_COUNT = 0;
		}
	}
	return AnalyzeResult;
}

//*******************************************************************/
//���ܣ�ɨ��EC11��ת�������Ķ��������������ظ�������������ʹ��
//�βΣ�EC11��ת������������-->>  unsigned char Set_EC11_TYPE  <<--  ��0----һ��λ��Ӧһ���壻1�����0��----����λ��Ӧһ����
//���أ�EC11��ת��������ɨ����-->>  char ScanResult  -->>  0���޶�����1����ת�� -1����ת��2��ֻ���°�����3�����Ű�����ת��-3�����Ű�����ת
//��⣺ֻɨ��EC11��ת��������û�ж������������ǵڼ��ΰ��°����򳤰���˫��������ֱֵ����Ϊ�βδ��� [ void Encoder_EC11_Analyze(char EC11_Value); ] ����ʹ��
//*******************************************************************/
char Encoder_EC11_Scan()
{
		//���´���A��B��һ��ֵ�ı�������Ϊ��̬ȫ�ֱ����������EC11��Ӧ��IO������ʼ��
		//  static char EC11_A_Last = 0;
		//  static char EC11_B_Last = 0;
	char ScanResult = 0;    //���ر�����ɨ���������ڷ����������Ķ���
                          //����ֵ��ȡֵ��   0���޶�����      1����ת��           8����ת��  
                          //                 2��ֻ���°�����  3�����Ű�����ת��   9�����Ű�����ת
                          //======================================================//
	if(EC11_Type == 0)      //================һ��λ��Ӧһ�����EC11================//
	{                     	//======================================================//
		if(EC11_A_Now != EC11_A_Last)   //��AΪʱ�ӣ�BΪ���ݡ���תʱAB���࣬��תʱABͬ��
		{
			if(EC11_A_Now == 0)
			{
				if(EC11_B_Now ==1)      //ֻ��Ҫ�ɼ�A�������ػ��½��ص�����һ��״̬����A�½���ʱBΪ1����ת                    
					 ScanResult = 1;     //��ת
				else                    //��ת
					 ScanResult = 8;
			}
			EC11_A_Last = EC11_A_Now;   //���±�������һ��״̬�ݴ����
			EC11_B_Last = EC11_B_Now;   //���±�������һ��״̬�ݴ����
		}
	}   
                          //======================================================//
	else                    //================����λ��Ӧһ�����EC11================//
	{                       //======================================================//
		if(EC11_A_Now !=EC11_A_Last)        //��A��������ʱ�ɼ�B��ǰ��״̬������B����һ�ε�״̬���жԱȡ�
		{                                   //��A 0->1 ʱ��B 1->0 ��ת����A 1->0 ʱ��B 0->1 ��ת��
                                        //��A 0->1 ʱ��B 0->1 ��ת����A 1->0 ʱ��B 1->0 ��ת
			if(EC11_A_Now == 1)     					//EC11_A����һ��״̬��ȣ�Ϊ������
			{
				if((EC11_B_Last == 1)&&(EC11_B_Now == 0))   //EC11_B����һ��״̬��ȣ�Ϊ�½���
						ScanResult = 1;                         //��ת
        if((EC11_B_Last == 0)&&(EC11_B_Now == 1))   //EC11_B����һ��״̬��ȣ�Ϊ������               
            ScanResult = 8;                        //��ת
                //>>>>>>>>>>>>>>>>����Ϊ��תһ���ٷ�ת��תһ������ת����<<<<<<<<<<<<<<<<//
        if((EC11_B_Last == EC11_B_Now)&&(EC11_B_Now == 0))  //A������ʱ���ɼ���B������Ϊ0
            ScanResult = 1;                                 //��ת
        if((EC11_B_Last == EC11_B_Now)&&(EC11_B_Now == 1))  //A������ʱ���ɼ���B������Ϊ1
            ScanResult = 8;                                 //��ת
			}
			else                    //EC11_A����һ��״̬��ȣ�Ϊ�½���
			{
				if((EC11_B_Last == 1)&&(EC11_B_Now == 0))   //EC11_B����һ��״̬��ȣ�Ϊ�½���
						ScanResult = 8;                        //��ת
				if((EC11_B_Last == 0)&&(EC11_B_Now == 1))   //EC11_B����һ��״̬��ȣ�Ϊ������
						ScanResult = 1;                         //��ת
				//>>>>>>>>>>>>>>>>����Ϊ��תһ���ٷ�ת��תһ������ת����<<<<<<<<<<<<<<<<//
				if((EC11_B_Last == EC11_B_Now)&&(EC11_B_Now == 0))  //A������ʱ���ɼ���B������Ϊ0
						ScanResult = 8;                                //��ת
				if((EC11_B_Last == EC11_B_Now)&&(EC11_B_Now == 1))  //A������ʱ���ɼ���B������Ϊ1   
						ScanResult = 1;                                 //��ת
			}               
				EC11_A_Last = EC11_A_Now;   //���±�������һ��״̬�ݴ����
				EC11_B_Last = EC11_B_Now;   //���±�������һ��״̬�ݴ����
		}
	}                                                                       
	if(EC11_Key == 0)   //���EC11�İ������£�����û��EC11û��ת����
	{
//		if(ScanResult == 0)         //���°���ʱδת��
			 ScanResult = 2;         //����ֵΪ2
//		else
//		{
//			if(ScanResult == 1)     //���°���ʱ����ת
//				 ScanResult = 3;     //����ֵΪ3
//			if(ScanResult == 8)    //���°���ʱ��ת
//				 ScanResult = 9;    //����ֵΪ-3
//		}
	}
    return ScanResult;      //����ֵ��ȡֵ��   0���޶�����      1����ת��           8����ת��
}                           //             		 2��ֻ���°�����  3�����Ű�����ת��   9�����Ű�����ת












