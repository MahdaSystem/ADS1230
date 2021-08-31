#ifndef ADS1230_H
#define ADS1230_H
#include <stdint.h>
#include <stdbool.h>

// Important Notes:
// 1. Tie CLKIN to Low to Activate Internal Oscillator
// 2. Abrupt Changes in VIN need 5 Cycles for Reading Data to Get Correct Values
// 3. Because of Weird behaviour of SCLK Pin We Cannot Use SPI Interface In Microcontrolers
// 4. For Pin Configurations, Read Datasheet
// 5. All Reading Data Functions can work in Blocking or Non-blocking Mode (Choose it from ADS1230_Init function)
// Restrictions:
// SCLK Speed: 500KHz (Fixed)

#define Debug_Enable // Uncomment if you want to use (depends on printf in stdio.h)
#define ADCValueToVoltage(x/*ADCvalue*/,v/*VREFF*/,g/*gain*/)   (x * v /(0x7FFFF * g  * 2.0)) // Works

//#pragma anon_unions // Uncomment this line if yu are using Keil software
typedef union ADC_DATA_u
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
} ADC_DATA; // Do not edit this union!

// Input Values :
typedef struct ADS1220_Handler_s
{
  void (*ADC_SPI_READ_24bit)(uint8_t*); // Must be initialized (only when you want use SPI)
  void (*ADC_SCLK_HIGH)(void);          // Must be initialized
  void (*ADC_SCLK_LOW)(void);           // Must be initialized
  bool (*ADC_Read_DRDY_DOUT)(void);     // Must be initialized
  void (*ADC_PDWN_HIGH)(void);          // Can  be initialized (Not Important if user handles PDWN Pin so ADS1230_PowerDown functions Not work)
  void (*ADC_PDWN_LOW)(void);           // Can  be initialized (Not Important if user handles PDWN Pin so ADS1230_PowerDown functions Not work)
  void (*ADC_Gain_HIGH)(void);          // Can  be initialized (Not Important if user handles Gain Pin)
  void (*ADC_Gain_LOW)(void);           // Can  be initialized (Not Important if user handles Gain Pin)
  void (*ADC_Speed_HIGH)(void);         // Can  be initialized (Not Important if user handles Speed Pin)
  void (*ADC_Speed_LOW)(void);          // Can  be initialized (Not Important if user handles Speed Pin)
  void (*ADC_Delay_US)(uint32_t);       // Must be initialized (Place here your delay in MicroSecond)
  void (*ADC_Delay_MS)(uint32_t);       // Must be initialized (Place here your delay in MiliSecond)
  bool UseSPI;                          // ! This Variable Will Be Configured In ADS1230_Init Function
  bool SpeedMode;                       // ! This Variable Will Be Configured In ADS1230_Init Function
  bool BlockingMode;                    // ! This Variable Will Be Configured In ADS1230_Init Function
  ADC_DATA ADCDataVal;                  // !!! DO NOT USE OR EDIT THIS !!!
} ADS1220_Handler;

// Parameters:
// ADC_Gain:      0: 64    | 1: 128       - Not Important if user handles ADC_Gain
// ADC_Speed:     0: 10SPS | 1: 80SPS     - Not Important if user handles ADC_Speed
// ADC_Blocking:  0: non-Blocking Mode    - User Have to check DRDY Pin for Data Ready then use Read Functions
//                1: Blocking Mode        - All Read Functions check DRDY then Read Data
void ADS1230_Init(ADS1220_Handler *ADC_Handler, bool ADC_Gain, bool ADC_Speed, bool ADC_Blocking, bool UseSPI);

void ADS1230_PowerDown_Enable(ADS1220_Handler *ADC_Handler);

void ADS1230_PowerDown_Disable(ADS1220_Handler *ADC_Handler);

int32_t ADS1230_Standby_Enable(ADS1220_Handler *ADC_Handler); // Read Data, Then Go to Standby Mode

void ADS1230_Standby_Disable(ADS1220_Handler *ADC_Handler);

int32_t ADS1230_StandbyWithOffsetCalibration_Enable(ADS1220_Handler *ADC_Handler); // Read Data, Then Go to Standby Mode with Offset Calibration

void ADS1230_StandbyWithOffsetCalibration_Disable(ADS1220_Handler *ADC_Handler);

int32_t ADS1230_RegularRead(ADS1220_Handler *ADC_Handler); // Regular Read Data

int32_t ADS1230_OffsetCalibration(ADS1220_Handler *ADC_Handler); // Read Data, Then Offset Calibration

#endif
