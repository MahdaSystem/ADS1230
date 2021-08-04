#include "ADS1230.h"

#ifdef Debug_Enable
#include <stdio.h> // for debug
#define PROGRAMLOG(arg...) printf(arg)
#else
#define PROGRAMLOG(arg...)
#endif

#pragma anon_unions
typedef union ADC_DATA_u {
    struct 
    {
        uint32_t Zero :12;
        uint32_t Part1:1;
        uint32_t Part2:1;
        uint32_t Part3:1;
        uint32_t Part4:1;
        uint32_t Part5:1;
        uint32_t Part6:1;
        uint32_t Part7:1;
        uint32_t Part8:1;
        uint32_t Part9:1;
        uint32_t Part10:1;
        uint32_t Part11:1;
        uint32_t Part12:1;
        uint32_t Part13:1;
        uint32_t Part14:1;
        uint32_t Part15:1;
        uint32_t Part16:1;
        uint32_t Part17:1;
        uint32_t Part18:1;
        uint32_t Part19:1;
        uint32_t Part20:1;
    };
    int32_t INT32Value;
} ADC_DATA;

static ADC_DATA   ADCDataVal = {0};
static bool       SpeedMode = 0;      // 0: 10SPS | 1: 80SPS
static bool       BlockingMode = 0;   // 0: non-Blocking Mode (User Have to chack DRDY Pin for Data Ready) | 1: Blocking Mode (It checks DRDY then Read Data)

void ADS1230_Init(ADS1220_Handler *ADC_Handler,bool ADC_Gain/*0: 64 | 1: 128*/,bool ADC_Speed/*0: 10SPS | 1: 80SPS*/,bool ADC_Blocking /*0: non-Blocking Mode (User Have to chack DRDY Pin for Data Ready then use Read Functions) | 1: Blocking Mode (All Read Functions check DRDY then Read Data)*/)
{
    if(!ADC_Handler) return;

    if(ADC_Gain) {if(ADC_Handler->ADC_Gain_HIGH) ADC_Handler->ADC_Gain_HIGH();}
    else         {if(ADC_Handler->ADC_Gain_LOW) ADC_Handler->ADC_Gain_LOW();}
    Delay_US(1);
    if(ADC_Speed) {if(ADC_Handler->ADC_Speed_HIGH) ADC_Handler->ADC_Speed_HIGH();}
    else          {if(ADC_Handler->ADC_Speed_LOW) ADC_Handler->ADC_Speed_LOW();}
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    SpeedMode = ADC_Speed;
    BlockingMode = ADC_Blocking;
}

void ADS1230_PowerDown_Enable(ADS1220_Handler *ADC_Handler)
{
    if(ADC_Handler->ADC_PDWN_LOW) ADC_Handler->ADC_PDWN_LOW();
    Delay_US(30);
}

void ADS1230_PowerDown_Disable(ADS1220_Handler *ADC_Handler)
{
    if(ADC_Handler->ADC_PDWN_HIGH) ADC_Handler->ADC_PDWN_HIGH();
    if(SpeedMode) Delay_US(410000); else Delay_US(55000);
}

int32_t ADS1230_Standby_Enable(ADS1220_Handler *ADC_Handler)
{
    if(BlockingMode) while (ADC_Handler->ADC_Read_DRDY_DOUT()); // For checking DRDY

    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part20 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part19 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part18 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part17 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part16 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part15 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part14 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part13 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part12 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part11 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part10 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part9 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part8 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part7 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part6 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part5 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part4 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part3 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part2 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADCDataVal.Part1 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(25);
    return ADCDataVal.INT32Value / 4096;
}

void ADS1230_Standby_Disable(ADS1220_Handler *ADC_Handler)
{
    ADC_Handler->ADC_SCLK_LOW();
    if (SpeedMode) Delay_US(410000); else Delay_US(55000);
}

int32_t ADS1230_StandbyWithOffsetCalibration_Enable(ADS1220_Handler *ADC_Handler)
{
    if(BlockingMode) while (ADC_Handler->ADC_Read_DRDY_DOUT()); // For checking DRDY

    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part20 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part19 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part18 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part17 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part16 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part15 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part14 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part13 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part12 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part11 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part10 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part9 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part8 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part7 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part6 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part5 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part4 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part3 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part2 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part1 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 21th
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 22th
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 23th
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 24th
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 25th
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 26th
    Delay_US(25);
    return ADCDataVal.INT32Value / 4096;
}

void ADS1230_StandbyWithOffsetCalibration_Disable(ADS1220_Handler *ADC_Handler)
{
    ADC_Handler->ADC_SCLK_LOW();
    if (SpeedMode) Delay_US(810000); else Delay_US(110000);
}

int32_t ADS1230_RegularRead(ADS1220_Handler *ADC_Handler)
{
    if(BlockingMode) while (ADC_Handler->ADC_Read_DRDY_DOUT()); // For checking DRDY

    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part20 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part19 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part18 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part17 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part16 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part15 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part14 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part13 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part12 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part11 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part10 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part9 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part8 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part7 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part6 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part5 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part4 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part3 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part2 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part1 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 21th SCLK to force DRDY/Dout to HIGH
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    return ADCDataVal.INT32Value / 4096;
}

int32_t ADS1230_OffsetCalibration(ADS1220_Handler *ADC_Handler)
{
    if(BlockingMode) while (ADC_Handler->ADC_Read_DRDY_DOUT()); // For checking DRDY

    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part20 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part19 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part18 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part17 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part16 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part15 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part14 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part13 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part12 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part11 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part10 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part9 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part8 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part7 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part6 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part5 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part4 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part3 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part2 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADCDataVal.Part1 = ADC_Handler->ADC_Read_DRDY_DOUT();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 21th SCLK to force DRDY/Dout to HIGH
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 22th
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 23th
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 24th
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 25th
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 26th for Offset Calibration
    Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    if (SpeedMode) Delay_US(110000); else Delay_US(810000);
    return ADCDataVal.INT32Value / 4096;
}
