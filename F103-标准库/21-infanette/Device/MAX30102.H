//******************************************************************************/
//  功能描述   : MAX30102读取心率血氧数据(STM32系列)
// 修改历史   :
// 日    期   :
// 作    者   :
// 修改内容   : 创建文件
//版权所有，盗版必究。
//******************************************************************************/
#ifndef __MAX30102_H_
#define __MAX30102_H_
#include "stm32f10x.h"
#include "stdbool.h"



//---------------------------------- 宏定义IO口  ----------------------------------------------//

#define Max30102_RCC_Port()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)		/* GPIO端口时钟 */

#define Max30102_SCL_Port		GPIOB							/* GPIO端口 */
#define Max30102_SCL_PIN		GPIO_Pin_13						/* GPIO引脚 */

#define Max30102_SDA_Port		GPIOB							
#define Max30102_SDA_PIN		GPIO_Pin_12		



/*************************** 定义读写SCL和SDA的宏 ***************************/
#define Max30102_SCL(a)			if(a)	\
								GPIO_SetBits(Max30102_SCL_Port,Max30102_SCL_PIN);\
								else		\
								GPIO_ResetBits(Max30102_SCL_Port,Max30102_SCL_PIN)
#define Max30102_SDA(a)			if(a)	\
								GPIO_SetBits(Max30102_SDA_Port,Max30102_SDA_PIN);\
								else		\
								GPIO_ResetBits(Max30102_SDA_Port,Max30102_SDA_PIN)
							
								
								
								
								

#define Max30102_SCL_READ()		 GPIO_ReadInputDataBit(Max30102_SCL_Port,Max30102_SCL_PIN)
#define Max30102_SDA_READ()		 GPIO_ReadInputDataBit(Max30102_SDA_Port,Max30102_SDA_PIN)
#define Max30102_INT_READ()		 GPIO_ReadInputDataBit(Max30102_INT_Port,Max30102_INT_PIN)



#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */



#define I2C_WRITE_ADDR 0xAE
#define I2C_READ_ADDR 0xAF

//register addresses
#define REG_INTR_STATUS_1 0x00
#define REG_INTR_STATUS_2 0x01
#define REG_INTR_ENABLE_1 0x02
#define REG_INTR_ENABLE_2 0x03
#define REG_FIFO_WR_PTR 0x04
#define REG_OVF_COUNTER 0x05
#define REG_FIFO_RD_PTR 0x06
#define REG_FIFO_DATA 0x07
#define REG_FIFO_CONFIG 0x08
#define REG_MODE_CONFIG 0x09
#define REG_SPO2_CONFIG 0x0A
#define REG_LED1_PA 0x0C
#define REG_LED2_PA 0x0D
#define REG_PILOT_PA 0x10
#define REG_MULTI_LED_CTRL1 0x11
#define REG_MULTI_LED_CTRL2 0x12
#define REG_TEMP_INTR 0x1F
#define REG_TEMP_FRAC 0x20
#define REG_TEMP_CONFIG 0x21
#define REG_PROX_INT_THRESH 0x30
#define REG_REV_ID 0xFE
#define REG_PART_ID 0xFF




void MAX30102_GPIO_Init(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);


bool maxim_max30102_init(void);
bool maxim_max30102_read_fifo(uint32_t *pun_red_led, uint32_t *pun_ir_led);
bool maxim_max30102_write_reg(uint8_t uch_addr, uint8_t uch_data);
bool maxim_max30102_read_reg(uint8_t uch_addr, uint8_t *puch_data);
bool maxim_max30102_reset(void);



#define FS 50    //sampling frequency
#define BUFFER_SIZE  (FS* 3) 
#define MA4_SIZE  4 // DONOT CHANGE
#define min(x,y) ((x) < (y) ? (x) : (y))


static  int32_t an_x[ BUFFER_SIZE]; //ir
static  int32_t an_y[ BUFFER_SIZE]; //red

void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer, int32_t n_ir_buffer_length, uint32_t *pun_red_buffer, int32_t *pn_spo2, int8_t *pch_spo2_valid, int32_t *pn_heart_rate, int8_t *pch_hr_valid);
void maxim_find_peaks(int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height, int32_t n_min_distance, int32_t n_max_num);
void maxim_peaks_above_min_height(int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height);
void maxim_remove_close_peaks(int32_t *pn_locs, int32_t *pn_npks, int32_t *pn_x, int32_t n_min_distance);
void maxim_sort_ascend(int32_t  *pn_x, int32_t n_size);
void maxim_sort_indices_descend(int32_t  *pn_x, int32_t *pn_indx, int32_t n_size);


extern int32_t heat_value;
extern int32_t spo2_value;
extern int8_t ReadMAX30102OK;
extern void Max30102_Heart_Spo2_Value(void);





#endif
