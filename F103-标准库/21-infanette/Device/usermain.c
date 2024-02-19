#include "usermain.h"
#include "usercode.h"




uint8_t SysState = 0;
DHT11_Data_TypeDef dht11_data;

//====================================FLSH存取
void Flsh_SavaData()
{
    Write_flsh_byte(0x0801FC00, Temp_H);
    Write_flsh_byte(0x0801F800, Temp_L);
    Write_flsh_byte(0x0801F400, Humi_H);
    Write_flsh_byte(0x0801F000, Humi_L);
    Write_flsh_byte(0x0801EC00, Heart_H);
    Write_flsh_byte(0x0801E800, Heart_L);
    Write_flsh_byte(0x0801E400, Spo2_H);
    Write_flsh_byte(0x0801E000, Spo2_L);
}
void Flsh_ReadData()
{
    Temp_H = readFlash(0x0801FC00);
    Temp_L = readFlash(0x0801F800);
    Humi_H = readFlash(0x0801F400);
    Humi_L = readFlash(0x0801F000);
    Heart_H = readFlash(0x0801EC00);
    Heart_L = readFlash(0x0801E800);
    Spo2_H = readFlash(0x0801E400);
    Spo2_L = readFlash(0x0801E000);

    if (Temp_H > 100)          Temp_H = 20;
    if (Temp_L > 100)          Temp_L = 12;
    if (Humi_H > 100)          Humi_H = 60;
    if (Humi_L > 100)          Humi_L = 20;
    if (Heart_H > 150)         Heart_H = 90;
    if (Heart_L > 150)         Heart_L = 40;
    if (Spo2_H > 100)          Spo2_H = 100;
    if (Spo2_L > 100)          Spo2_L = 70;
}



//====================================DHT11获取温湿度
void DHT11_GetHumi()
{
    Dht11_ReadData(&dht11_data);
    if (Dht11Flag)
    {
        Dht11Flag = 0;
        Humi = dht11_data.Hum;
    }
}

//------------- 获取温度、心率 -------------------
void Get_dat_value()
{
    if (TempFlag && ReadMAX30102data == 0)
    {
        TempFlag = 0;
        Temp = DS18B20_Get_Temp();
    }
    if (ReadMAX30102data)
    {
        Max30102_Heart_Spo2_Value();
        if (ReadMAX30102OK)
        {
            ReadMAX30102OK = 0;
            Heart = heat_value;
            Spo2 = spo2_value;
            ReadMAX30102data = 0;
        }

        if (MAX30102Time == 0 && SysState >= 2)
        {
            Spo2 = Heart = 0;
            ReadMAX30102data = 0;
        }
    }
}



//====================================按键处理
void Key_Dispose()
{
    if (Keyvalue)
    {
        switch (Keyvalue)
        {
        case 0:

            break;
        case 1:
            SysFace = (SysFace + 1) % 9;
            if (SysFace == 0)      Flsh_SavaData();

            break;
        case 2:
            switch (SysFace)
            {
            case 0:
                BeepFlag = 0;
                break;
            case 1:
                if (Temp_H < 99)       Temp_H++;
                break;
            case 2:
                if (Temp_L < Temp_H - 1) Temp_L++;
                break;
            case 3:
                if (Humi_H < 99)       Humi_H++;
                break;
            case 4:
                if (Humi_L < Humi_H - 1) Humi_L++;
                break;
            case 5:
                if (Heart_H < 150)     Heart_H++;
                break;
            case 6:
                if (Heart_L < Heart_H - 1)   Heart_L++;
                break;
            case 7:
                if (Spo2_H < 100)      Spo2_H++;
                break;
            case 8:
                if (Spo2_L < Spo2_H - 1) Spo2_L++;
                break;
            }
            break;
        case 3:
            switch (SysFace)
            {
            case 0:
                MAX30102Time = 30;  //-- 测量心率30s倒计时
                ReadMAX30102data = 1;
                break;
            case 1:
                if (Temp_H > Temp_L + 1)     Temp_H--;
                break;
            case 2:
                if (Temp_L > 0)            Temp_L--;
                break;
            case 3:
                if (Humi_H > Humi_L + 1)     Humi_H--;
                break;
            case 4:
                if (Humi_L > 0)            Humi_L--;
                break;
            case 5:
                if (Heart_H > Heart_L + 1)       Heart_H--;
                break;
            case 6:
                if (Heart_L > 0)               Heart_L--;
                break;
            case 7:
                if (Spo2_H > Spo2_L + 1)         Spo2_H--;
                break;
            case 8:
                if (Spo2_L > 0)                Spo2_L--;
                break;

            }
            break;
        }
        Keyvalue = 0;
    }

}

//------------------------- OLED显示 -----------------------------------
void OLED_Display(void)
{
    OLED_Init();
    display_GB2312_string(0, 0, "湿度");
    Display_Byte(0, 2, Humi / 10 % 10);
    Display_Byte(0, 4, Humi / 10 % 10);



}












