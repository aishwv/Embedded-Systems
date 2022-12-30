/*
Aishwarya Venkatesh
1966425
12/04/2022
This program contains initialization functions to set up the LCD and then fill it
with red color
*/

#include "SSD2119_Display.h"
#include "tm4c1294ncpdt.h"

void LCD_Init(void);
void LCD_PrintFloat(float num);

int main() {
  LCD_Init();
  while(1) {
    LCD_ColorFill(((0xAA>>3)<<11) | ((0x00>>2)<<5) | (0x00>>3)); // Red
  }
}