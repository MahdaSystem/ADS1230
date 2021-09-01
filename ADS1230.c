/**
 **********************************************************************************
 * @file   ADS1230.c
 * @author Ali Moallem (https://github.com/AliMoal)
 * @brief  
 *         Functionalities of the this file:
 *          + 
 *          + 
 *          + 
 **********************************************************************************
 *
 *! Copyright (c) 2021 Mahda Embedded System (MIT License)
 *!
 *! Permission is hereby granted, free of charge, to any person obtaining a copy
 *! of this software and associated documentation files (the "Software"), to deal
 *! in the Software without restriction, including without limitation the rights
 *! to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *! copies of the Software, and to permit persons to whom the Software is
 *! furnished to do so, subject to the following conditions:
 *!
 *! The above copyright notice and this permission notice shall be included in all
 *! copies or substantial portions of the Software.
 *!
 *! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *! IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *! FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *! AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *! LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *! OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *! SOFTWARE.
 *!
 **********************************************************************************
 **/

//* Private Includes -------------------------------------------------------------- //
#include "ADS1230.h"

//* Others ------------------------------------------------------------------------ //
#ifdef Debug_Enable
#include <stdio.h> // for debug
#define PROGRAMLOG(arg...) printf(arg)
#else
#define PROGRAMLOG(arg...)
#endif

/**
 ** ==================================================================================
 **                           ##### Public Functions #####                               
 ** ==================================================================================
 **/

/**
 * @brief  Initializes The ADC and Library
 * @note   User MUST call this at the the begining of the program ONCE!
 * @param  ADC_Handler:   Pointer Of Library Handler
 * @param  ADC_Gain:      ADC Gain
 *         @note          Not Important if user handles ADC_Speed
 *                        - 0: 64
 *                        - 1: 128
 * @param  ADC_Speed:     ADC Speed
 *         @note          Not Important if user handles ADC_Speed
 *                        - 0: 10SPS
 *                        - 1: 80SPS
 * @param  ADC_Blocking:  ADC Blocking
 *                        - 0: non-Blocking Mode    - User Have to check DRDY Pin for Data Ready then use Read Functions
 *                        - 1: Blocking Mode        - All Read Functions check DRDY then Read Data
 * @param  UseSPI:        using SPI or GPIO to communicate with ADC
 *                        - 0: Use GPIO for reading data
 *                        - 1: Use SPI for reading data 
 * @retval None
 */
void
ADS1230_Init(ADS1230_Handler_t *ADC_Handler, bool ADC_Gain, bool ADC_Speed, bool ADC_Blocking, bool UseSPI)
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

/**
 * @brief  Enables Power-Down mode Of ADC
 * @note   If you want use this function, You have to configure ADC_PDWN_LOW in ADS1230_Handler
 * @param  ADC_Handler: 
 * @retval None
 */
void
ADS1230_PowerDown_Enable(ADS1230_Handler_t *ADC_Handler)
{
  if (ADC_Handler->ADC_PDWN_LOW)
    ADC_Handler->ADC_PDWN_LOW();
  ADC_Handler->ADC_Delay_US(30);
}

/**
 * @brief  Disables Power-Down mode Of ADC
 * @note   If you want use this function, You have to configure ADC_PDWN_HIGH in ADS1230_Handler
 * @param  ADC_Handler: 
 * @retval None
 */
void
ADS1230_PowerDown_Disable(ADS1230_Handler_t *ADC_Handler)
{
  if (ADC_Handler->ADC_PDWN_HIGH)
    ADC_Handler->ADC_PDWN_HIGH();
  if (ADC_Handler->SpeedMode)
    ADC_Handler->ADC_Delay_MS(50);
  else
    ADC_Handler->ADC_Delay_MS(400);
}

/**
 * @brief  Reads data Then Enables Standby Mode of ADC
 * @param  ADC_Handler: 
 * @retval ADC Raw Data
 */
int32_t
ADS1230_Standby_Enable(ADS1230_Handler_t *ADC_Handler)
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

/**
 * @brief  Disables Standby Mode Of ADC
 * @param  ADC_Handler: 
 * @retval None
 */
void
ADS1230_Standby_Disable(ADS1230_Handler_t *ADC_Handler)
{
  ADC_Handler->ADC_SCLK_LOW();
  if (ADC_Handler->SpeedMode)
    ADC_Handler->ADC_Delay_MS(55);
  else
    ADC_Handler->ADC_Delay_MS(410);
}

/**
 * @brief  Reads data Then Enables Standby Mode of ADC With Offset Calibration
 * @param  ADC_Handler: 
 * @retval ADC Raw Data
 */
int32_t
ADS1230_StandbyWithOffsetCalibration_Enable(ADS1230_Handler_t *ADC_Handler)
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

/**
 * @brief  Disables Standby Mode Of ADC With Offset Calibration
 * @param  ADC_Handler: 
 * @retval None
 */
void
ADS1230_StandbyWithOffsetCalibration_Disable(ADS1230_Handler_t *ADC_Handler)
{
  ADC_Handler->ADC_SCLK_LOW();
  if (ADC_Handler->SpeedMode)
    ADC_Handler->ADC_Delay_MS(110);
  else
    ADC_Handler->ADC_Delay_MS(810);
}

/**
 * @brief  Regular Read Data
 * @param  ADC_Handler: 
 * @retval ADC Raw Data
 */
int32_t
ADS1230_RegularRead(ADS1230_Handler_t *ADC_Handler)
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

/**
 * @brief   Read Data Then Offset Calibration
 * @param  ADC_Handler: 
 * @retval ADC Raw Data
 */
int32_t
ADS1230_OffsetCalibration(ADS1230_Handler_t *ADC_Handler)
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
