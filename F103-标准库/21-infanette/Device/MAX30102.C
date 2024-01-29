#include "MAX30102.h"




uint32_t aun_ir_buffer[500]; //infrared LED sensor data
uint32_t aun_red_buffer[500];  //red LED sensor data
int32_t n_ir_buffer_length; //data length
int32_t n_spo2;  //SPO2 value
int8_t ch_spo2_valid;  //indicator to show if the SPO2 calculation is valid
int32_t n_heart_rate; //heart rate value
int8_t  ch_hr_valid;  //indicator to show if the heart rate calculation is valid
uint8_t uch_dummy;


int32_t heat_value;
int32_t spo2_value;
int8_t ReadMAX30102OK;





#define max30102_WR_address 0xAE
const uint8_t uch_spo2_table[184] = { 95, 95, 95, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 98, 98, 99, 99, 99, 99,
                                      99, 99, 99, 99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
                                      100, 100, 100, 100, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 97, 97,
                                      97, 97, 96, 96, 96, 96, 95, 95, 95, 94, 94, 94, 93, 93, 93, 92, 92, 92, 91, 91,
                                      90, 90, 89, 89, 89, 88, 88, 87, 87, 86, 86, 85, 85, 84, 84, 83, 82, 82, 81, 81,
                                      80, 80, 79, 78, 78, 77, 76, 76, 75, 74, 74, 73, 72, 72, 71, 70, 69, 69, 68, 67,
                                      66, 66, 65, 64, 63, 62, 62, 61, 60, 59, 58, 57, 56, 56, 55, 54, 53, 52, 51, 50,
                                      49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 31, 30, 29,
                                      28, 27, 26, 25, 23, 22, 21, 20, 19, 17, 16, 15, 14, 12, 11, 10, 9, 7, 6, 5,
                                      3, 2, 1
                                    } ;

									
									
void MAX30102_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	Max30102_RCC_Port();

    //设置GPIO的基本参数
    GPIO_InitStruct.GPIO_Pin = Max30102_SCL_PIN | Max30102_SDA_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;    //输出速度2MHz
    GPIO_Init(Max30102_SCL_Port, &GPIO_InitStruct);
    i2c_Stop();

    maxim_max30102_reset(); //resets the MAX30102
    maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_dummy); //Reads/clears the interrupt status register
    maxim_max30102_init();  //initialize the MAX30102
}



//---------------------------------------------------- 延时函数
void i2c_Delay(void)
{
    uint8_t i;
    /*　
        CPU主频168MHz时，在内部Flash运行, MDK工程不优化。用台式示波器观测波形。
        循环次数为5时，SCL频率 = 1.78MHz (读耗时: 92ms, 读写正常，但是用示波器探头碰上就读写失败。时序接近临界)
        循环次数为10时，SCL频率 = 1.1MHz (读耗时: 138ms, 读速度: 118724B/s)
        循环次数为30时，SCL频率 = 440KHz， SCL高电平时间1.0us，SCL低电平时间1.2us

        上拉电阻选择2.2K欧时，SCL上升沿时间约0.5us，如果选4.7K欧，则上升沿约1us

        实际应用选择400KHz左右的速率即可
    */
    for (i = 0; i < 30; i++);
}




//---------------------------------------------------- 起始信号
void i2c_Start(void)
{
    /* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
    Max30102_SDA(1);
    Max30102_SCL(1);
    i2c_Delay();
    Max30102_SDA(0);
    i2c_Delay();
    Max30102_SCL(0);
    i2c_Delay();
}


//---------------------------------------------------- 停止信号
void i2c_Stop(void)
{
    /* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
    Max30102_SDA(0);
    Max30102_SCL(1);
    i2c_Delay();
    Max30102_SDA(1);
    i2c_Delay();
}


/*
*********************************************************************************************************
*   函 数 名: i2c_SendByte
*   功能说明: CPU向I2C总线设备发送8bit数据
*   形    参:  _ucByte ： 等待发送的字节
*   返 回 值: 无
*********************************************************************************************************
*/
void i2c_SendByte(uint8_t _ucByte)
{
    uint8_t i;

    /* 先发送字节的高位bit7 */
    for (i = 0; i < 8; i++)
    {
        if (_ucByte & 0x80)
        {
            Max30102_SDA(1);
        }
        else
        {
            Max30102_SDA(0);
        }
        i2c_Delay();
        Max30102_SCL(1);
        i2c_Delay();
        Max30102_SCL(0);
        if (i == 7)
        {
            Max30102_SDA(1); // 释放总线
        }
        _ucByte <<= 1;  /* 左移一个bit */
        i2c_Delay();
    }
}


/*
*********************************************************************************************************
*   函 数 名: i2c_ReadByte
*   功能说明: CPU从I2C总线设备读取8bit数据
*   形    参:  无
*   返 回 值: 读到的数据
*********************************************************************************************************
*/
uint8_t i2c_ReadByte(void)
{
    uint8_t i;
    uint8_t value;

    /* 读到第1个bit为数据的bit7 */
    value = 0;
    for (i = 0; i < 8; i++)
    {
        value <<= 1;
        Max30102_SCL(1);
        i2c_Delay();
        if (Max30102_SDA_READ())
        {
            value++;
        }
        Max30102_SCL(0);
        i2c_Delay();
    }
    return value;
}

/*
*********************************************************************************************************
*   函 数 名: i2c_WaitAck
*   功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*   形    参:  无
*   返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/
uint8_t i2c_WaitAck(void)
{
    uint8_t re;

    Max30102_SDA(1);;   /* CPU释放SDA总线 */
    i2c_Delay();
    Max30102_SCL(1);;   /* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
    i2c_Delay();
    if (Max30102_SDA_READ())    /* CPU读取SDA口线状态 */
    {
        re = 1;
    }
    else
    {
        re = 0;
    }
    Max30102_SCL(0);;
    i2c_Delay();
    return re;
}

/*
*********************************************************************************************************
*   函 数 名: i2c_Ack
*   功能说明: CPU产生一个ACK信号
*   形    参:  无
*   返 回 值: 无
*********************************************************************************************************
*/
void i2c_Ack(void)
{
    Max30102_SDA(0);    /* CPU驱动SDA = 0 */
    i2c_Delay();
    Max30102_SCL(1);    /* CPU产生1个时钟 */
    i2c_Delay();
    Max30102_SCL(0);
    i2c_Delay();
    Max30102_SDA(1);    /* CPU释放SDA总线 */
}

/*
*********************************************************************************************************
*   函 数 名: i2c_NAck
*   功能说明: CPU产生1个NACK信号
*   形    参:  无
*   返 回 值: 无
*********************************************************************************************************
*/
void i2c_NAck(void)
{
    Max30102_SDA(1);    /* CPU驱动SDA = 1 */
    i2c_Delay();
    Max30102_SCL(1);    /* CPU产生1个时钟 */
    i2c_Delay();
    Max30102_SCL(0);
    i2c_Delay();
}

/*
*********************************************************************************************************
*   函 数 名: i2c_CheckDevice
*   功能说明: 检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断该设备是否存在
*   形    参:  _Address：设备的I2C总线地址
*   返 回 值: 返回值 0 表示正确， 返回1表示未探测到
*********************************************************************************************************
*/
uint8_t i2c_CheckDevice(uint8_t _Address)
{
    uint8_t ucAck;
    if (Max30102_SDA_READ() && Max30102_SCL_READ())
    {
        i2c_Start();        /* 发送启动信号 */
        /* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
        i2c_SendByte(_Address | I2C_WR);
        ucAck = i2c_WaitAck();  /* 检测设备的ACK应答 */
        i2c_Stop();         /* 发送停止信号 */
        return ucAck;
    }
    return 1;   /* I2C总线异常 */
}







bool maxim_max30102_write_reg(uint8_t uch_addr, uint8_t uch_data)
{
    i2c_Start();
    i2c_SendByte(max30102_WR_address | I2C_WR); /* 此处是写指令 */
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;  /* EEPROM器件无应答 */
    }
    i2c_SendByte(uch_addr);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;  /* EEPROM器件无应答 */
    }
    i2c_SendByte(uch_data);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;  /* EEPROM器件无应答 */
    }
    i2c_Stop();
    return true;    /* 执行成功 */
cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
    /* 发送I2C总线停止信号 */
    i2c_Stop();
    return false;
}

bool maxim_max30102_read_reg(uint8_t uch_addr, uint8_t *puch_data)
{
    i2c_Start();
    i2c_SendByte(max30102_WR_address | I2C_WR); /* 此处是写指令 */
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;  /* EEPROM器件无应答 */
    }
    i2c_SendByte((uint8_t)uch_addr);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;  /* EEPROM器件无应答 */
    }
    i2c_Start();
    i2c_SendByte(max30102_WR_address | I2C_RD); /* 此处是读指令 */
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;  /* EEPROM器件无应答 */
    }
    {
        *puch_data = i2c_ReadByte();    /* 读1个字节 */

        i2c_NAck(); /* 最后1个字节读完后，CPU产生NACK信号(驱动SDA = 1) */
    }
    i2c_Stop();
    return true;    /* 执行成功 返回data值 */
cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
    /* 发送I2C总线停止信号 */
    i2c_Stop();
    return false;
}
bool maxim_max30102_init(void)
{
    if (!maxim_max30102_write_reg(REG_INTR_ENABLE_1, 0xc0)) // INTR setting
        return false;
    if (!maxim_max30102_write_reg(REG_INTR_ENABLE_2, 0x00))
        return false;
    if (!maxim_max30102_write_reg(REG_FIFO_WR_PTR, 0x00)) //FIFO_WR_PTR[4:0]
        return false;
    if (!maxim_max30102_write_reg(REG_OVF_COUNTER, 0x00)) //OVF_COUNTER[4:0]
        return false;
    if (!maxim_max30102_write_reg(REG_FIFO_RD_PTR, 0x00)) //FIFO_RD_PTR[4:0]
        return false;
    if (!maxim_max30102_write_reg(REG_FIFO_CONFIG, 0x6f)) //sample avg = 8, fifo rollover=false, fifo almost full = 17
        return false;
    if (!maxim_max30102_write_reg(REG_MODE_CONFIG, 0x03)) //0x02 for Red only, 0x03 for SpO2 mode 0x07 multimode LED
        return false;
    if (!maxim_max30102_write_reg(REG_SPO2_CONFIG, 0x2F)) // SPO2_ADC range = 4096nA, SPO2 sample rate (400 Hz), LED pulseWidth (411uS)
        return false;

    if (!maxim_max30102_write_reg(REG_LED1_PA, 0x17)) //Choose value for ~ 4.5mA for LED1
        return false;
    if (!maxim_max30102_write_reg(REG_LED2_PA, 0x17)) // Choose value for ~ 4.5mA for LED2
        return false;
    if (!maxim_max30102_write_reg(REG_PILOT_PA, 0x7f)) // Choose value for ~ 25mA for Pilot LED
        return false;
    return true;
}

bool maxim_max30102_read_fifo(uint32_t *pun_red_led, uint32_t *pun_ir_led)
{
    uint32_t un_temp;
    uint8_t uch_temp;
    *pun_ir_led = 0;
    *pun_red_led = 0;
    maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_temp);
    maxim_max30102_read_reg(REG_INTR_STATUS_2, &uch_temp);
    i2c_Start();
    i2c_SendByte(max30102_WR_address | I2C_WR); /* 此处是写指令 */
    if (i2c_WaitAck() != 0)
    {
//        printf("read fifo failed");
        goto cmd_fail;  /* EEPROM器件无应答 */
    }
    i2c_SendByte((uint8_t)REG_FIFO_DATA);
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;  /* EEPROM器件无应答 */
    }
    i2c_Start();
    i2c_SendByte(max30102_WR_address | I2C_RD); /* 此处是读指令 */
    if (i2c_WaitAck() != 0)
    {
        goto cmd_fail;  /* EEPROM器件无应答 */
    }

    un_temp = i2c_ReadByte();
    i2c_Ack();
    un_temp <<= 16;
    *pun_red_led += un_temp;
    un_temp = i2c_ReadByte();
    i2c_Ack();
    un_temp <<= 8;
    *pun_red_led += un_temp;
    un_temp = i2c_ReadByte();
    i2c_Ack();
    *pun_red_led += un_temp;

    un_temp = i2c_ReadByte();
    i2c_Ack();
    un_temp <<= 16;
    *pun_ir_led += un_temp;
    un_temp = i2c_ReadByte();
    i2c_Ack();
    un_temp <<= 8;
    *pun_ir_led += un_temp;
    un_temp = i2c_ReadByte();
    i2c_Ack();
    *pun_ir_led += un_temp;
    *pun_red_led &= 0x03FFFF; //Mask MSB [23:18]
    *pun_ir_led &= 0x03FFFF; //Mask MSB [23:18]
    i2c_Stop();
    return true;
cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
    /* 发送I2C总线停止信号 */
    i2c_Stop();
    return false;
}


bool maxim_max30102_reset()
{
    if (!maxim_max30102_write_reg(REG_MODE_CONFIG, 0x40))
        return false;
    else
        return true;
}



void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer, int32_t n_ir_buffer_length, uint32_t *pun_red_buffer, int32_t *pn_spo2, int8_t *pch_spo2_valid,
        int32_t *pn_heart_rate, int8_t *pch_hr_valid)
{
    uint32_t un_ir_mean ;
    int32_t k, n_i_ratio_count;
    int32_t i, n_exact_ir_valley_locs_count, n_middle_idx;
    int32_t n_th1, n_npks;
    int32_t an_ir_valley_locs[15] ;
    int32_t n_peak_interval_sum;

    int32_t n_y_ac, n_x_ac;
    int32_t n_spo2_calc;
    int32_t n_y_dc_max, n_x_dc_max;
    int32_t n_y_dc_max_idx, n_x_dc_max_idx;
    int32_t an_ratio[5], n_ratio_average;
    int32_t n_nume, n_denom ;

    // calculates DC mean and subtract DC from ir
    un_ir_mean = 0;
    for (k = 0 ; k < n_ir_buffer_length ; k++) un_ir_mean += pun_ir_buffer[k] ;
    un_ir_mean = un_ir_mean / n_ir_buffer_length ;

    // remove DC and invert signal so that we can use peak detector as valley detector
    for (k = 0 ; k < n_ir_buffer_length ; k++)
        an_x[k] = -1 * (pun_ir_buffer[k] - un_ir_mean) ;

    // 4 pt Moving Average
    for (k = 0; k < BUFFER_SIZE - MA4_SIZE; k++)
    {
        an_x[k] = (an_x[k] + an_x[k + 1] + an_x[k + 2] + an_x[k + 3]) / (int)4;
    }
    // calculate threshold
    n_th1 = 0;
    for (k = 0 ; k < BUFFER_SIZE ; k++)
    {
        n_th1 +=  an_x[k];
    }
    n_th1 =  n_th1 / (BUFFER_SIZE);
    if (n_th1 < 30) n_th1 = 30; // min allowed
    if (n_th1 > 60) n_th1 = 60; // max allowed

    for (k = 0 ; k < 15; k++) an_ir_valley_locs[k] = 0;
    // since we flipped signal, we use peak detector as vSalley detector
    maxim_find_peaks(an_ir_valley_locs, &n_npks, an_x, BUFFER_SIZE, n_th1, 4, 15);  //peak_height, peak_distance, max_num_peaks
    n_peak_interval_sum = 0;
    if (n_npks >= 2)
    {
        for (k = 1; k < n_npks; k++) n_peak_interval_sum += (an_ir_valley_locs[k] - an_ir_valley_locs[k - 1]) ;
        n_peak_interval_sum = n_peak_interval_sum / (n_npks - 1);
        *pn_heart_rate = (int32_t)((FS * 60) / n_peak_interval_sum);
        *pch_hr_valid  = 1;
    }
    else
    {
        *pn_heart_rate = -999; // unable to calculate because # of peaks are too small
        *pch_hr_valid  = 0;
    }

    //  load raw value again for SPO2 calculation : RED(=y) and IR(=X)
    for (k = 0 ; k < n_ir_buffer_length ; k++)
    {
        an_x[k] =  pun_ir_buffer[k] ;
        an_y[k] =  pun_red_buffer[k] ;
    }

    // find precise min near an_ir_valley_locs
    n_exact_ir_valley_locs_count = n_npks;

    //using exact_ir_valley_locs , find ir-red DC andir-red AC for SPO2 calibration an_ratio
    //finding AC/DC maximum of raw

    n_ratio_average = 0;
    n_i_ratio_count = 0;
    for (k = 0; k < 5; k++) an_ratio[k] = 0;
    for (k = 0; k < n_exact_ir_valley_locs_count; k++)
    {
        if (an_ir_valley_locs[k] > BUFFER_SIZE)
        {
            *pn_spo2 =  -999 ; // do not use SPO2 since valley loc is out of range
            *pch_spo2_valid  = 0;
            return;
        }
    }
    // find max between two valley locations
    // and use an_ratio betwen AC compoent of Ir & Red and DC compoent of Ir & Red for SPO2
    for (k = 0; k < n_exact_ir_valley_locs_count - 1; k++)
    {
        n_y_dc_max = -16777216 ;
        n_x_dc_max = -16777216;
        if (an_ir_valley_locs[k + 1] - an_ir_valley_locs[k] > 3)
        {
            for (i = an_ir_valley_locs[k]; i < an_ir_valley_locs[k + 1]; i++)
            {
                if (an_x[i] > n_x_dc_max)
                {
                    n_x_dc_max = an_x[i];
                    n_x_dc_max_idx = i;
                }
                if (an_y[i] > n_y_dc_max)
                {
                    n_y_dc_max = an_y[i];
                    n_y_dc_max_idx = i;
                }
            }
            n_y_ac = (an_y[an_ir_valley_locs[k + 1]] - an_y[an_ir_valley_locs[k] ]) * (n_y_dc_max_idx - an_ir_valley_locs[k]);  //red
            n_y_ac =  an_y[an_ir_valley_locs[k]] + n_y_ac / (an_ir_valley_locs[k + 1] - an_ir_valley_locs[k])  ;
            n_y_ac =  an_y[n_y_dc_max_idx] - n_y_ac;   // subracting linear DC compoenents from raw
            n_x_ac = (an_x[an_ir_valley_locs[k + 1]] - an_x[an_ir_valley_locs[k] ]) * (n_x_dc_max_idx - an_ir_valley_locs[k]);  // ir
            n_x_ac =  an_x[an_ir_valley_locs[k]] + n_x_ac / (an_ir_valley_locs[k + 1] - an_ir_valley_locs[k]);
            n_x_ac =  an_x[n_y_dc_max_idx] - n_x_ac;     // subracting linear DC compoenents from raw
            n_nume = (n_y_ac * n_x_dc_max) >> 7 ;  //prepare X100 to preserve floating value
            n_denom = (n_x_ac * n_y_dc_max) >> 7;
            if (n_denom > 0  && n_i_ratio_count < 5 &&  n_nume != 0)
            {
                an_ratio[n_i_ratio_count] = (n_nume * 100) / n_denom ; //formular is ( n_y_ac *n_x_dc_max) / ( n_x_ac *n_y_dc_max) ;
                n_i_ratio_count++;
            }
        }
    }
    // choose median value since PPG signal may varies from beat to beat
    maxim_sort_ascend(an_ratio, n_i_ratio_count);
    n_middle_idx = n_i_ratio_count / 2;

    if (n_middle_idx > 1)
        n_ratio_average = (an_ratio[n_middle_idx - 1] + an_ratio[n_middle_idx]) / 2;  // use median
    else
        n_ratio_average = an_ratio[n_middle_idx ];

    if (n_ratio_average > 2 && n_ratio_average < 184)
    {
        n_spo2_calc = uch_spo2_table[n_ratio_average] ;
        *pn_spo2 = n_spo2_calc ;
        *pch_spo2_valid  = 1;//  float_SPO2 =  -45.060*n_ratio_average* n_ratio_average/10000 + 30.354 *n_ratio_average/100 + 94.845 ;  // for comparison with table
    }
    else
    {
        *pn_spo2 =  -999 ; // do not use SPO2 since signal an_ratio is out of range
        *pch_spo2_valid  = 0;
    }
}


void maxim_find_peaks(int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height, int32_t n_min_distance, int32_t n_max_num)
/**
* \brief        Find peaks
* \par          Details
*               Find at most MAX_NUM peaks above MIN_HEIGHT separated by at least MIN_DISTANCE
*
* \retval       None
*/
{
    maxim_peaks_above_min_height(pn_locs, n_npks, pn_x, n_size, n_min_height);
    maxim_remove_close_peaks(pn_locs, n_npks, pn_x, n_min_distance);
    *n_npks = min(*n_npks, n_max_num);
}

void maxim_peaks_above_min_height(int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height)
/**
* \brief        Find peaks above n_min_height
* \par          Details
*               Find all peaks above MIN_HEIGHT
*
* \retval       None
*/
{
    int32_t i = 1, riseFound = 0, holdOff1 = 0, holdOff2 = 0, holdOffThresh = 4;
    *n_npks = 0;

    while (i < n_size - 1)
    {
        if (holdOff2 == 0)
        {
            if (pn_x[i] > n_min_height && pn_x[i] > pn_x[i - 1])     // find left edge of potential peaks
            {
                riseFound = 1;
            }
            if (riseFound == 1)
            {
                if ((pn_x[i] < n_min_height) && (holdOff1 < holdOffThresh))     // if false edge
                {
                    riseFound = 0;
                    holdOff1 = 0;
                }
                else
                {
                    if (holdOff1 == holdOffThresh)
                    {
                        if ((pn_x[i] < n_min_height) && (pn_x[i - 1] >= n_min_height))
                        {
                            if ((*n_npks) < 15)
                            {
                                pn_locs[(*n_npks)++] = i;   // peak is right edge
                            }
                            holdOff1 = 0;
                            riseFound = 0;
                            holdOff2 = 8;
                        }
                    }
                    else
                    {
                        holdOff1 = holdOff1 + 1;
                    }
                }
            }
        }
        else
        {
            holdOff2 = holdOff2 - 1;
        }
        i++;
    }
}

void maxim_remove_close_peaks(int32_t *pn_locs, int32_t *pn_npks, int32_t *pn_x, int32_t n_min_distance)
/**
* \brief        Remove peaks
* \par          Details
*               Remove peaks separated by less than MIN_DISTANCE
*
* \retval       None
*/
{

    int32_t i, j, n_old_npks, n_dist;

    /* Order peaks from large to small */
    maxim_sort_indices_descend(pn_x, pn_locs, *pn_npks);

    for (i = -1; i < *pn_npks; i++)
    {
        n_old_npks = *pn_npks;
        *pn_npks = i + 1;
        for (j = i + 1; j < n_old_npks; j++)
        {
            n_dist =  pn_locs[j] - (i == -1 ? -1 : pn_locs[i]);   // lag-zero peak of autocorr is at index -1
            if (n_dist > n_min_distance || n_dist < -n_min_distance)
                pn_locs[(*pn_npks)++] = pn_locs[j];
        }
    }

    // Resort indices int32_to ascending order
    maxim_sort_ascend(pn_locs, *pn_npks);
}

void maxim_sort_ascend(int32_t  *pn_x, int32_t n_size)
/**
* \brief        Sort array
* \par          Details
*               Sort array in ascending order (insertion sort algorithm)
*
* \retval       None
*/
{
    int32_t i, j, n_temp;
    for (i = 1; i < n_size; i++)
    {
        n_temp = pn_x[i];
        for (j = i; j > 0 && n_temp < pn_x[j - 1]; j--)
            pn_x[j] = pn_x[j - 1];
        pn_x[j] = n_temp;
    }
}

void maxim_sort_indices_descend(int32_t  *pn_x, int32_t *pn_indx, int32_t n_size)
/**
* \brief        Sort indices
* \par          Details
*               Sort indices according to descending order (insertion sort algorithm)
*
* \retval       None
*/
{
    int32_t i, j, n_temp;
    for (i = 1; i < n_size; i++)
    {
        n_temp = pn_indx[i];
        for (j = i; j > 0 && pn_x[n_temp] > pn_x[pn_indx[j - 1]]; j--)
            pn_indx[j] = pn_indx[j - 1];
        pn_indx[j] = n_temp;
    }
}

//============================================================================================================================== 获取心率血氧数据函数
void Max30102_Heart_Spo2_Value()
{
    int32_t i;
    n_ir_buffer_length = 200;


    for (i = 0; i < n_ir_buffer_length; i++)
    {
        maxim_max30102_read_fifo((aun_red_buffer + i), (aun_ir_buffer + i)); //read from MAX30102 FIFO
    }
    maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);
    if ((ch_hr_valid == 1) && (ch_spo2_valid == 1) && (n_spo2 > 90)  && (n_spo2 < 100) && (n_heart_rate < 120) && (n_heart_rate > 50))
    {
        if (n_heart_rate > 80)
        {
            n_heart_rate = n_heart_rate - 30;
            n_heart_rate = (n_heart_rate + 68) / 2;
        }
        heat_value = n_heart_rate;
        spo2_value = n_spo2;
        ReadMAX30102OK = 1;
    }
}





