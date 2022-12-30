/*
Aishwarya Venkatesh
1966425
12/04/2022
This program uses the LCD Display and Touch modules to switch between two clock 
frequencies and print the temperature and clock frequencies on the LCD
*/
#include <stdint.h>
#include "Lab4Task1c_Inits.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include "lab4task1c.h"

// FUNCTION PROTOTYPES
void LCD_Init(void);
void LCD_PrintFloat(float num);
void LCD_SetCursor(unsigned short xPos, unsigned short yPos);
void LCD_PrintString(char data[]);
void Touch_Init(void);

uint32_t ADC_value;
float temperature;
enum frequency freq;


int main(void) {
  LCD_Init();               // Initialize LCD
  Switch_Init();            // Initialize the 2 onboard switches (GPIO)
  UART_Init();              // Initialize UART2
  ADCReadPot_Init();        // Initialize ADC0 to read from the potentiometer  
  TimerADCTriger_Init();    // Initialize Timer0A to trigger ADC0  
  Touch_Init();
  while(1) { 
    temperature = 147.5 - ((247.5 * ADC_value) / 4096.0);
    LCD_DrawFilledCircle(60, 200, 30, ((0xFF>>3)<<11) | ((0x55>>2)<<5) | (0x55>>3));
    LCD_DrawFilledCircle(260, 200, 30, ((0x55>>3)<<11) | ((0xFF>>2)<<5) | (0x55>>3));
    LCD_SetCursor(240, 200);
    LCD_PrintString("120 MHz");
    LCD_SetCursor(40, 200);
    LCD_PrintString("12 MHz");
    long xPos = Touch_ReadX();
    long yPos = Touch_ReadY();
    if (xPos > 2000 && yPos < 1500) {
      freq = PRESET1; // 120 MHz
      PLL_Init(freq);
    }
    else if (xPos < 2000 && yPos < 1500) {
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

