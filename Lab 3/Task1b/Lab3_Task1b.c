/*
Aishwarya Venkatesh
1966425
11/29/2022
This program implements an ADC module that reads the internal temperature and
prints to terminal and changes clock frequency based on the on board switch press
*/

#include <stdint.h>
#include "Lab3_Inits.h"

#include "lab3task1b.h"

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset  
  Switch_Init();            // Initialize the 2 onboard switches (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  while(1) {
    float temperature;
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.2: Change the temperature based on the button press
    if (GPIODATA_J == 0x02) {
      enum frequency freq = PRESET1; // 120 MHz
      PLL_Init(freq);        // Set system clock frequency to 120 MHz
      temperature = 147.5 - ((247.5 * ADC_value) / 4096.0);
      printf("%f\n", temperature);
    }
    else if (GPIODATA_J == 0x01) {
      enum frequency freq = PRESET3; // 12 MHz
      PLL_Init(freq);        // Set system clock frequency to 12 MHz
      temperature = 147.5 - ((247.5 * ADC_value) / 4096.0);
      printf("%f\n", temperature);
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
