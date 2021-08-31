#include "ADS1230.h"

#ifdef Debug_Enable
#include <stdio.h> // for debug
#define PROGRAMLOG(arg...) printf(arg)
#else
#define PROGRAMLOG(arg...)
#endif

void ADS1230_Init(ADS1220_Handler *ADC_Handler, bool ADC_Gain /*0: 64 | 1: 128*/, bool ADC_Speed /*0: 10SPS | 1: 80SPS*/, bool ADC_Blocking /*0: non-Blocking Mode (User Have to chack DRDY Pin for Data Ready then use Read Functions) | 1: Blocking Mode (All Read Functions check DRDY then Read Data)*/, bool UseSPI)
{
  if (!ADC_Handler)
    return;

  if (ADC_Gain)
  {
    if (ADC_Handler->ADC_Gain_HIGH)
      ADC_Handler->ADC_Gain_HIGH();
  }
  else
  {
    if (ADC_Handler->ADC_Gain_LOW)
      ADC_Handler->ADC_Gain_LOW();
  }
  ADC_Handler->ADC_Delay_US(1);
  if (ADC_Speed)
  {
    if (ADC_Handler->ADC_Speed_HIGH)
      ADC_Handler->ADC_Speed_HIGH();
  }
  else
  {
    if (ADC_Handler->ADC_Speed_LOW)
      ADC_Handler->ADC_Speed_LOW();
  }
  ADC_Handler->ADC_Delay_US(1);
  ADC_Handler->ADC_SCLK_LOW();
  ADC_Handler->ADC_Delay_US(1);
  ADC_Handler->UseSPI = UseSPI;
  ADC_Handler->SpeedMode = ADC_Speed;
  ADC_Handler->BlockingMode = ADC_Blocking;
  if (ADC_Handler->ADC_PDWN_HIGH)
  {
    ADC_Handler->ADC_PDWN_HIGH();
    if (ADC_Handler->SpeedMode)
      ADC_Handler->ADC_Delay_MS(55);
    else
      ADC_Handler->ADC_Delay_MS(410);
  }
}

void ADS1230_PowerDown_Enable(ADS1220_Handler *ADC_Handler)
{
  if (ADC_Handler->ADC_PDWN_LOW)
    ADC_Handler->ADC_PDWN_LOW();
  ADC_Handler->ADC_Delay_US(30);
}

void ADS1230_PowerDown_Disable(ADS1220_Handler *ADC_Handler)
{
  if (ADC_Handler->ADC_PDWN_HIGH)
    ADC_Handler->ADC_PDWN_HIGH();
  if (ADC_Handler->SpeedMode)
    ADC_Handler->ADC_Delay_MS(50);
  else
    ADC_Handler->ADC_Delay_MS(400);
}

int32_t ADS1230_Standby_Enable(ADS1220_Handler *ADC_Handler)
{
  if (ADC_Handler->BlockingMode)
    while (ADC_Handler->ADC_Read_DRDY_DOUT()); // For checking DRDY

  if (ADC_Handler->UseSPI)
  {
    uint8_t Buffer[3];
    ADC_Handler->ADC_SPI_READ_24bit(Buffer);
    ADC_Handler->ADCDataVal.Byte1 = Buffer[0];
    ADC_Handler->ADCDataVal.Byte2 = Buffer[1];
    ADC_Handler->ADCDataVal.Byte3 = Buffer[2];
    ADC_Handler->ADCDataVal.Zero = 0;
  }
  else
  {
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part20 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part19 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part18 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part17 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part16 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part15 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part14 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part13 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part12 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part11 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part10 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part9 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part8 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part7 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part6 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part5 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part4 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part3 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part2 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADCDataVal.Part1 = ADC_Handler->ADC_Read_DRDY_DOUT();
  }
  ADC_Handler->ADC_Delay_US(25);
  return ADC_Handler->ADCDataVal.INT32Value / 4096;
}

void ADS1230_Standby_Disable(ADS1220_Handler *ADC_Handler)
{
  ADC_Handler->ADC_SCLK_LOW();
  if (ADC_Handler->SpeedMode)
    ADC_Handler->ADC_Delay_MS(55);
  else
    ADC_Handler->ADC_Delay_MS(410);
}

int32_t ADS1230_StandbyWithOffsetCalibration_Enable(ADS1220_Handler *ADC_Handler)
{
  if (ADC_Handler->BlockingMode)
    while (ADC_Handler->ADC_Read_DRDY_DOUT()); // For checking DRDY

  if (ADC_Handler->UseSPI)
  {
    uint8_t Buffer[3];
    ADC_Handler->ADC_SPI_READ_24bit(Buffer);
    ADC_Handler->ADCDataVal.Byte1 = Buffer[0];
    ADC_Handler->ADCDataVal.Byte2 = Buffer[1];
    ADC_Handler->ADCDataVal.Byte3 = Buffer[2];
    ADC_Handler->ADCDataVal.Zero = 0;
  }
  else
  {
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part20 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part19 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part18 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part17 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part16 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part15 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part14 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part13 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part12 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part11 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part10 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part9 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part8 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part7 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part6 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part5 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part4 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part3 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part2 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part1 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 21st
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 22nd
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 23rd
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 24th
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADC_Delay_US(1);
  }
  ADC_Handler->ADC_SCLK_HIGH(); // 25th
  ADC_Handler->ADC_Delay_US(1);
  ADC_Handler->ADC_SCLK_LOW();
  ADC_Handler->ADC_Delay_US(1);
  ADC_Handler->ADC_SCLK_HIGH(); // 26th
  ADC_Handler->ADC_Delay_US(25);
  return ADC_Handler->ADCDataVal.INT32Value / 4096;
}

void ADS1230_StandbyWithOffsetCalibration_Disable(ADS1220_Handler *ADC_Handler)
{
  ADC_Handler->ADC_SCLK_LOW();
  if (ADC_Handler->SpeedMode)
    ADC_Handler->ADC_Delay_MS(110);
  else
    ADC_Handler->ADC_Delay_MS(810);
}

int32_t ADS1230_RegularRead(ADS1220_Handler *ADC_Handler)
{
  if (ADC_Handler->BlockingMode)
    while (ADC_Handler->ADC_Read_DRDY_DOUT()); // For checking DRDY

  if (ADC_Handler->UseSPI)
  {
    uint8_t Buffer[3];
    ADC_Handler->ADC_SPI_READ_24bit(Buffer);
    ADC_Handler->ADCDataVal.Byte1 = Buffer[0];
    ADC_Handler->ADCDataVal.Byte2 = Buffer[1];
    ADC_Handler->ADCDataVal.Byte3 = Buffer[2];
    ADC_Handler->ADCDataVal.Zero = 0;
  }
  else
  {
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part20 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part19 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part18 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part17 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part16 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part15 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part14 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part13 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part12 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part11 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part10 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part9 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part8 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part7 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part6 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part5 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part4 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part3 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part2 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part1 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 21st SCLK to force DRDY/Dout to HIGH
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
  }
  return ADC_Handler->ADCDataVal.INT32Value / 4096;
}

int32_t ADS1230_OffsetCalibration(ADS1220_Handler *ADC_Handler)
{
  if (ADC_Handler->BlockingMode)
    while (ADC_Handler->ADC_Read_DRDY_DOUT()); // For checking DRDY

  if (ADC_Handler->UseSPI)
  {
    uint8_t Buffer[3];
    ADC_Handler->ADC_SPI_READ_24bit(Buffer);
    ADC_Handler->ADCDataVal.Byte1 = Buffer[0];
    ADC_Handler->ADCDataVal.Byte2 = Buffer[1];
    ADC_Handler->ADCDataVal.Byte3 = Buffer[2];
    ADC_Handler->ADCDataVal.Zero = 0;
  }
  else
  {
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part20 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part19 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part18 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part17 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part16 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part15 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part14 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part13 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part12 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part11 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part10 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part9 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part8 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part7 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part6 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part5 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part4 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part3 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part2 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADCDataVal.Part1 = ADC_Handler->ADC_Read_DRDY_DOUT();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 21st SCLK to force DRDY/Dout to HIGH
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 22nd
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 23rd
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_HIGH(); // 24th
    ADC_Handler->ADC_Delay_US(1);
    ADC_Handler->ADC_SCLK_LOW();
    ADC_Handler->ADC_Delay_US(1);
  }
  ADC_Handler->ADC_SCLK_HIGH(); // 25th
  ADC_Handler->ADC_Delay_US(1);
  ADC_Handler->ADC_SCLK_LOW();
  ADC_Handler->ADC_Delay_US(1);
  ADC_Handler->ADC_SCLK_HIGH(); // 26th for Offset Calibration
  ADC_Handler->ADC_Delay_US(1);
  ADC_Handler->ADC_SCLK_LOW();
  if (ADC_Handler->SpeedMode)
    ADC_Handler->ADC_Delay_US(110000);
  else
    ADC_Handler->ADC_Delay_US(810000);
  return ADC_Handler->ADCDataVal.INT32Value / 4096;
}
