/*
Aishwarya Venkatesh
1966425
12/04/2022
This program uses the LCD Display to print out the current onboard temperature
and the current frequency of the clock
*/

#include <stdint.h>
#include "Lab4Task1b_Inits.h"
#include "SSD2119_Display.h"
#include "tm4c1294ncpdt.h"
#include "lab4task1b.h"

//FUNCTION PROTOTYPES
void LCD_Init(void);
void LCD_PrintFloat(float num);
void LCD_SetCursor(unsigned short xPos, unsigned short yPos);
void LCD_PrintString(char data[]);

uint32_t ADC_value;
float temperature;
enum frequency freq;


int main(void) {
  LCD_Init();               // Initialize LCD
  Switch_Init();            // Initialize the 2 onboard switches (GPIO)
  ADCReadPot_Init();        // Initialize ADC0 to read from the potentiometer  
  TimerADCTriger_Init();    // Initialize Timer0A to trigger ADC0  
  while(1) { 
    temperature = 147.5 - ((247.5 * ADC_value) / 4096.0);
    if (GPIODATA_J == 0x02) {
      freq = PRESET1; // 120 MHz
      PLL_Init(freq);
    }
    else if (GPIODATA_J == 0x01) {
      freq = PRESET3; // 12 MHz
      PLL_Init(freq);
    }
    LCD_SetCursor(0, 0);
    LCD_PrintString("The current temperature is ");
    LCD_PrintFloat(temperature);
    LCD_PrintString(" C, ");
    float fahrenheit = (temperature * 9 / 5) + 32;
    LCD_PrintFloat(fahrenheit);
    LCD_PrintString(" F.");
    LCD_PrintChar('\n');
    LCD_PrintString("The current clock frequency is ");
    LCD_PrintInteger(freq);
    LCD_PrintString(" MHz.");
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  GPTMICR |= 0x01;
  ADCISC |= 0x8;
  ADC_value = ADCSSFIFO3;
}
