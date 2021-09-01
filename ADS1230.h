/**
 **********************************************************************************
 * @file   ADS1230.h
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
//* Define to prevent recursive inclusion ---------------------------------------- //
#ifndef ADS1230_H
#define ADS1230_H

#ifdef __cplusplus
extern "C" {
#endif

//* Includes ---------------------------------------------------------------------- //
#include <stdint.h>
#include <stdbool.h>

//? User Configurations and Notes ------------------------------------------------- //
// ! Important Notes:
// 1. Tie CLKIN to Low to Activate Internal Oscillator (referred to Datasheet)
// 2. Abrupt Changes in VIN need 5 Cycles for Reading Data to Get Correct Values (referred to Datasheet)
// 4. For Pin Configurations, Read Datasheet
// 5. All Reading Data Functions can work in Blocking or Non-blocking Mode (Choose it from ADS1230_Init function)
// ! Restrictions:
// SCLK Speed for Non-SPI Mode: 500KHz (Fixed)
#define USE_MACRO_DELAY         1           // 0: Use handler delay ,So you have to set ADC_Delay in Handler | 1: use Macro delay, So you have to set MACRO_DELAY Macro
//#define MACRO_DELAY_US(x)                   // If you want to use Macro delay, place your delay function in microseconds here
//#define MACRO_DELAY_MS(x)                   // If you want to use Macro delay, place your delay function in miliseconds here
#define Debug_Enable                        // Uncomment if you want to use (depends on printf in stdio.h)
//#pragma anon_unions                         // Uncomment this line if yu are using Keil software
//? ------------------------------------------------------------------------------- //

//* Defines and Macros ------------------------------------------------------------ //
#define ADCValueToVoltage(x/*ADCvalue*/,v/*VREFF*/,g/*Gain*/) \
        (x * v /(524287.0f * g  * 2.0))   // Use this to convert ADC value to Voltage - It Works
#define ADCValueToWeightKG(x/*ADCvalue*/,fs/*Full Scale in KG*/,s/*Sensitivity in mVolt*/,g/*Gain*/) \
        (x * fs  /(524.287f * 2 * g * s)) // Use this to convert ADC value to Weight (LOADCELL) - It Works

//! DO NOT USE OR EDIT THIS BLOCK ------------------------------------------------- //
#if USE_MACRO_DELAY == 0
#define Delay_US(x)   ADS131_Handler->ADC_Delay_US(x)
#define Delay_MS(x)   ADS131_Handler->ADC_Delay_MS(x)
#else
#define Delay_US(x)   MACRO_DELAY_US(x)
#define Delay_MS(x)   MACRO_DELAY_MS(x)
#ifndef MACRO_DELAY_US
#error "MACRO_DELAY_US is not defined. Please Use handler delay or config MACRO_DELAY_US macro, You can choose it on USE_MACRO_DELAY define"
#endif
#ifndef MACRO_DELAY_MS
#error "MACRO_DELAY_MS is not defined. Please Use handler delay or config MACRO_DELAY_MS macro, You can choose it on USE_MACRO_DELAY define"
#endif
#endif

typedef union
ADC_DATA_u
{
  struct
  {
    uint32_t Zero : 12;
    uint32_t Part1 : 1;
    uint32_t Part2 : 1;
    uint32_t Part3 : 1;
    uint32_t Part4 : 1;
    uint32_t Part5 : 1;
    uint32_t Part6 : 1;
    uint32_t Part7 : 1;
    uint32_t Part8 : 1;
    uint32_t Part9 : 1;
    uint32_t Part10 : 1;
    uint32_t Part11 : 1;
    uint32_t Part12 : 1;
    uint32_t Part13 : 1;
    uint32_t Part14 : 1;
    uint32_t Part15 : 1;
    uint32_t Part16 : 1;
    uint32_t Part17 : 1;
    uint32_t Part18 : 1;
    uint32_t Part19 : 1;
    uint32_t Part20 : 1;
  };
  struct
  {
    uint32_t Zero2 : 8;
    uint32_t Byte3 : 8;
    uint32_t Byte2 : 8;
    uint32_t Byte1 : 8;
  };
  int32_t INT32Value;
} ADC_DATA_t;
//! ------------------------------------------------------------------------------- //

/**
 ** ==================================================================================
 **                               ##### Structs #####                               
 ** ==================================================================================
 **/

/**
 * @brief  Handling Library
 * @note   User MUST configure This at the begining of the program before ADS1230_Init
 */
typedef struct
ADS1230_Handler_s
{
  void (*ADC_SPI_READ_24bit)(uint8_t*); //! Must be initialized If you want use SPI
  void (*ADC_SCLK_HIGH)(void);          // Must be initialized 
  void (*ADC_SCLK_LOW)(void);           // Must be initialized
  bool (*ADC_Read_DRDY_DOUT)(void);     // Must be initialized
  void (*ADC_PDWN_HIGH)(void);          // Can  be initialized (Not Important if user handles PDWN Pin so ADS1230_PowerDown_Disable function will Not work)
  void (*ADC_PDWN_LOW)(void);           // Can  be initialized (Not Important if user handles PDWN Pin so ADS1230_PowerDown_Enable function will Not work)
  void (*ADC_Gain_HIGH)(void);          // Can  be initialized (Not Important if user handles Gain Pin)
  void (*ADC_Gain_LOW)(void);           // Can  be initialized (Not Important if user handles Gain Pin)
  void (*ADC_Speed_HIGH)(void);         // Can  be initialized (Not Important if user handles Speed Pin)
  void (*ADC_Speed_LOW)(void);          // Can  be initialized (Not Important if user handles Speed Pin)
  void (*ADC_Delay_US)(uint32_t);       //! Must be initialized If You do not use Macro Delay (Place here your delay in MicroSecond)
  void (*ADC_Delay_MS)(uint32_t);       //! Must be initialized If You do not use Macro Delay (Place here your delay in MiliSecond)
  bool UseSPI;                          //! This Variable Will Be Configured In ADS1230_Init Function, DO NOT USE OR EDIT THIS!
  bool SpeedMode;                       //! This Variable Will Be Configured In ADS1230_Init Function, DO NOT USE OR EDIT THIS!
  bool BlockingMode;                    //! This Variable Will Be Configured In ADS1230_Init Function, DO NOT USE OR EDIT THIS!
  ADC_DATA_t ADCDataVal;                //!!! DO NOT USE OR EDIT THIS !!!
} ADS1230_Handler_t;

/**
 ** ==================================================================================
 **                          ##### Public Functions #####                               
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
ADS1230_Init(ADS1230_Handler_t *ADC_Handler, bool ADC_Gain, bool ADC_Speed, bool ADC_Blocking, bool UseSPI);

/**
 * @brief  Enables Power-Down mode Of ADC
 * @note   If you want use this function, You have to configure ADC_PDWN_LOW in ADS1230_Handler
 * @param  ADC_Handler: 
 * @retval None
 */
void
ADS1230_PowerDown_Enable(ADS1230_Handler_t *ADC_Handler);

/**
 * @brief  Disables Power-Down mode Of ADC
 * @note   If you want use this function, You have to configure ADC_PDWN_HIGH in ADS1230_Handler
 * @param  ADC_Handler: 
 * @retval None
 */
void
ADS1230_PowerDown_Disable(ADS1230_Handler_t *ADC_Handler);

/**
 * @brief  Reads data Then Enables Standby Mode of ADC
 * @param  ADC_Handler: 
 * @retval ADC Raw Data
 */
int32_t
ADS1230_Standby_Enable(ADS1230_Handler_t *ADC_Handler);

/**
 * @brief  Disables Standby Mode Of ADC
 * @param  ADC_Handler: 
 * @retval None
 */
void
ADS1230_Standby_Disable(ADS1230_Handler_t *ADC_Handler);

/**
 * @brief  Reads data Then Enables Standby Mode of ADC With Offset Calibration
 * @param  ADC_Handler: 
 * @retval ADC Raw Data
 */
int32_t
ADS1230_StandbyWithOffsetCalibration_Enable(ADS1230_Handler_t *ADC_Handler);

/**
 * @brief  Disables Standby Mode Of ADC With Offset Calibration
 * @param  ADC_Handler: 
 * @retval None
 */
void
ADS1230_StandbyWithOffsetCalibration_Disable(ADS1230_Handler_t *ADC_Handler);

/**
 * @brief  Reads Data Regularly
 * @param  ADC_Handler: 
 * @retval ADC Raw Data
 */
int32_t
ADS1230_RegularRead(ADS1230_Handler_t *ADC_Handler);

/**
 * @brief  Reads Data Then Offset Calibration
 * @param  ADC_Handler: 
 * @retval ADC Raw Data
 */
int32_t
ADS1230_OffsetCalibration(ADS1230_Handler_t *ADC_Handler); // Read Data, Then Offset Calibration

#ifdef __cplusplus
}
#endif
#endif
