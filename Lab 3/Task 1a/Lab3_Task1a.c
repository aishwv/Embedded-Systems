/*
Aishwarya Venkatesh
1966425
11/29/2022
This program implements changes in LED function based on the resistance provided 
by the potentiometer measured by the ADC module
*/

#include <stdint.h>
#include "Lab3_Inits.h"
#include "lab3task1a.h"

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float resistance;
  while(1) {
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to resistance in kilo-ohm
    resistance = ADC_value / 4095.0 * 10.0;
    // 5.2: Change the pattern of LEDs based on the resistance
    if (resistance < 2.5) {
      GPIODATA_F = 0x0;
      GPIODATA_N = 0x2;
    } else if (resistance < 5.0) {
      GPIODATA_F = 0x0;
      GPIODATA_N = 0x3;
    } else if (resistance < 7.5) {
      GPIODATA_F = 0x10;
      GPIODATA_N = 0x3;
    } else {
      GPIODATA_F = 0x11;
      GPIODATA_N = 0x3;
    }
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  GPTMICR |= 0x01;
  ADCISC |= 0x8;
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3;
}
