#ifndef __EC11_H
#define __EC11_H

//#include "sys.h"
#include "stm32f10x.h"


/**************** IO口定义 *******************/
#define EC11_A_Now          GPIO_Pin_9      //CLK
#define EC11_B_Now          GPIO_Pin_8      //DT
#define EC11_Key            GPIO_Pin_7      //SW


static unsigned char EC11_NUM_SW = 0;


//----------------编码器参数微调宏定义----------------//
#define EC11_SCAN_PERIOD_MS            1                            //EC11编码器扫描周期
#define KEY_COUNT_DESHAKING         ( 10/EC11_SCAN_PERIOD_MS)       //按键消抖时间
#define KEY_COUNT_LONGTIME          (150/EC11_SCAN_PERIOD_MS)       //长按按键判断时间
#define KEY_COUNT_DUALCLICKTIME     (150/EC11_SCAN_PERIOD_MS)       //双击按键判断时间
#define KEY_LONG_REPEAT_TIME        (200/EC11_SCAN_PERIOD_MS)       //长按按键的回报率的倒数，即一直长按按键时响应的时间间隔



//----------------局部文件内变量列表----------------//
static  char    EC11_A_Last = 0;                        //EC11的A引脚上一次的状态
static  char    EC11_B_Last = 0;                        //EC11的B引脚上一次的状态
static  char    EC11_Type = 1;                          //定义变量暂存EC11的类型---->>>>----  0：一定位对应一脉冲；  1：两定位对应一脉冲
//所谓一定位对应一脉冲，是指EC11旋转编码器每转动一格，A和B都会输出一个完整的方波。
//而  两定位对应一脉冲，是指EC11旋转编码器每转动两格，A和B才会输出一个完整的方波，只转动一格只输出A和B的上升沿或下降沿

static   int    EC11_KEY_COUNT = 0;                     //EC11按键动作计数器
static   int    EC11_KEY_DoubleClick_Count = 0;         //EC11按键双击动作计数器
static  char    FLAG_EC11_KEY_ShotClick = 0;            //EC11按键短按动作标志
static  char    FLAG_EC11_KEY_LongClick = 0;            //EC11按键长按动作标志
static  char    FLAG_EC11_KEY_DoubleClick = 0;          //EC11按键双击动作标志





void EC11_Init(unsigned char Set_EC11_TYPE);
char Encoder_EC11_Analyze(char EC11_Value);
char Encoder_EC11_Scan(void);





#endif  /* __EC11_H */




