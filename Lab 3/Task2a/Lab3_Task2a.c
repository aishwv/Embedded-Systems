/*
Aishwarya Venkatesh
1966425
11/29/2022
This program uses UART serial communication to print the temperature readings
read by the ADC module to PuTTy
*/
#include <stdint.h>
#include "Lab3_Inits.h"

// STEP 0b: Include your header file here
#include "lab3task2a.h"

uint32_t ADC_value;
float temperature;

int main(void) {
  // Select system clock frequency preset  
  Switch_Init();            // Initialize the 2 onboard switches (GPIO)
  UART_Init();              // Initialize UART2
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer  
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0  
  while(1) {    
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to temperature   
    temperature = 147.5 - ((247.5 * ADC_value) / 4096.0);
    // 5.2: Change the frequency based on the button press
    if (GPIODATA_J == 0x02) {
      enum frequency freq = PRESET1; // 120 MHz
      PLL_Init(freq);        // Set system clock frequency to 120 MHz
    }
    else if (GPIODATA_J == 0x01) {
      enum frequency freq = PRESET3; // 12 MHz
      PLL_Init(freq);        // Set system clock frequency to 12 MHz
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
  // Send temperature readings to PuTTy
  char temp_arr[7];
  sprintf(temp_arr, "%lf", temperature);
  temp_arr[5] = '\r';
  temp_arr[6] = '\n';
  for (int i = 0; i < 7; i++){
    while((UARTFR & 0x20) != 0){}
    UARTDR = temp_arr[i];
  }
}
