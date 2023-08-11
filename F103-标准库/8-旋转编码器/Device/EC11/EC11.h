#ifndef __EC11_H
#define __EC11_H

//#include "sys.h"
#include "stm32f10x.h"


/**************** IO�ڶ��� *******************/
#define EC11_A_Now          GPIO_Pin_9      //CLK
#define EC11_B_Now          GPIO_Pin_8      //DT
#define EC11_Key            GPIO_Pin_7      //SW


static unsigned char EC11_NUM_SW = 0;


//----------------����������΢���궨��----------------//
#define EC11_SCAN_PERIOD_MS            1                            //EC11������ɨ������
#define KEY_COUNT_DESHAKING         ( 10/EC11_SCAN_PERIOD_MS)       //��������ʱ��
#define KEY_COUNT_LONGTIME          (150/EC11_SCAN_PERIOD_MS)       //���������ж�ʱ��
#define KEY_COUNT_DUALCLICKTIME     (150/EC11_SCAN_PERIOD_MS)       //˫�������ж�ʱ��
#define KEY_LONG_REPEAT_TIME        (200/EC11_SCAN_PERIOD_MS)       //���������Ļر��ʵĵ�������һֱ��������ʱ��Ӧ��ʱ����



//----------------�ֲ��ļ��ڱ����б�----------------//
static  char    EC11_A_Last = 0;                        //EC11��A������һ�ε�״̬
static  char    EC11_B_Last = 0;                        //EC11��B������һ�ε�״̬
static  char    EC11_Type = 1;                          //��������ݴ�EC11������---->>>>----  0��һ��λ��Ӧһ���壻  1������λ��Ӧһ����
//��νһ��λ��Ӧһ���壬��ָEC11��ת������ÿת��һ��A��B�������һ�������ķ�����
//��  ����λ��Ӧһ���壬��ָEC11��ת������ÿת������A��B�Ż����һ�������ķ�����ֻת��һ��ֻ���A��B�������ػ��½���

static   int    EC11_KEY_COUNT = 0;                     //EC11��������������
static   int    EC11_KEY_DoubleClick_Count = 0;         //EC11����˫������������
static  char    FLAG_EC11_KEY_ShotClick = 0;            //EC11�����̰�������־
static  char    FLAG_EC11_KEY_LongClick = 0;            //EC11��������������־
static  char    FLAG_EC11_KEY_DoubleClick = 0;          //EC11����˫��������־





void EC11_Init(unsigned char Set_EC11_TYPE);
char Encoder_EC11_Analyze(char EC11_Value);
char Encoder_EC11_Scan(void);





#endif  /* __EC11_H */




