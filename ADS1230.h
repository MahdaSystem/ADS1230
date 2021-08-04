#ifndef ADS1230_H
#define ADS1230_H

// For Delay
#include "main.h"
extern TIM_HandleTypeDef htim6;
__forceinline void Delay_us(uint32_t us) {
  htim6.Instance->CNT = 0;
  while(htim6.Instance->CNT < (us)) {}
} // for delay

// Important Notes:
// 1. Tie CLKIN to Low to Activate Internal Oscillator
// 2. Abrupt Changes in VIN need 5 Cycles for Reading Data to Get Correct Values
// 3. Because of Weird behaviour of SCLK Pin We Cannot Use SPI Interface In Microcontrolers
// 4. For Pin Configurations Read Datasheet
// Restrictions:
// SCLK Speed: 500KHz (Fixed)
#define Delay_US(x)           Delay_us(x)                     // Place your delay function in microseconds (Must be Initialized)
#define Debug_Enable                                          // Uncomment if you want to use (depends on printf in stdio.h)
// #define ADCValueToWeight(x,v)   (x * (double)v/*VREFF*/ / 0x7FFFF) // NOT WORK

// Input Values :
typedef struct ADS1220_Handler_s {
  void (*ADC_SCLK_HIGH)(void);                      // Must be initialized
  void (*ADC_SCLK_LOW)(void);                       // Must be initialized
  bool (*ADC_Read_DRDY_DOUT)(void);                 // Must be initialized
  void (*ADC_PDWN_HIGH)(void);                      // Can  be initialized (If You Want to Use ADS1230_PowerDown Functions)
  void (*ADC_PDWN_LOW)(void);                       // Can  be initialized (If You Want to Use ADS1230_PowerDown Functions)
  void (*ADC_Gain_HIGH)(void);                      // Can  be initialized
  void (*ADC_Gain_LOW)(void);                       // Can  be initialized
  void (*ADC_Speed_HIGH)(void);                     // Can  be initialized
  void (*ADC_Speed_LOW)(void);                      // Can  be initialized
} ADS1220_Handler;

void ADS1230_Init(ADS1220_Handler *ADC_Handler,bool ADC_Gain/*0: 64 | 1: 128*/,bool ADC_Speed/*0: 10SPS | 1: 80SPS*/);

void ADS1230_PowerDown_Enable(ADS1220_Handler *ADC_Handler);

void ADS1230_PowerDown_Disable(ADS1220_Handler *ADC_Handler);

int32_t ADS1230_Standby_Enable(ADS1220_Handler *ADC_Handler); // Read Data, Then Go to Standby Mode

void ADS1230_Standby_Disable(ADS1220_Handler *ADC_Handler);

int32_t ADS1230_StandbyWithOffsetCalibration_Enable(ADS1220_Handler *ADC_Handler); // Read Data, Then Go to Standby Mode with Offset Calibration

void ADS1230_StandbyWithOffsetCalibration_Disable(ADS1220_Handler *ADC_Handler);

int32_t ADS1230_RegularRead(ADS1220_Handler *ADC_Handler); // Regular Read Data

int32_t ADS1230_OffsetCalibration(ADS1220_Handler *ADC_Handler); // Read Data, Then Offset Calibration

#endif