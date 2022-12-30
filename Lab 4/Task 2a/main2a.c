/*
Aishwarya Venkatesh
1966425
12/04/2022
This program implements a traffic light system built with 2 off board push 
buttons and 3 LEDs depicting stop, warn and go states. There is a System On/Off 
button that turns on and off the whole system. There is also a Pedestrian button
that tells the system to go the warn state followed by the stop state if it is
go state.
*/

#include <stdint.h> 
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include "lab4task2a.h" 
#include "PLL_Header.h"

enum states{start, stop, warn, go} state;

void LCD_Init(void);
void LCD_PrintFloat(float num);
void LCD_SetCursor(unsigned short xPos, unsigned short yPos);
void LCD_PrintString(char data[]);
void Touch_Init(void);

long xPos;
long yPos;

int main(void) {
    LCD_Init();               // Initialize LCD
    Touch_Init();
    Timer_long_init();
    Timer_short0_init();
    Timer_short1_init();
    PLL_Init(PRESET2);
    state = start;
    while (1) {
      switch(state) { 
        case start:
          LCD_StartState();          
          xPos = Touch_ReadX();
          yPos = Touch_ReadY();
          if (system_switch_input() && !(GPTMCTL_short0 & 0x01)) { // System switch pressed and Short system timer off
            start_short0_timer(); // start short system timer
          }
          else if (!system_switch_input() && (GPTMCTL_short0 & 0x01)) { // System switch not pressed and short system timer on
            GPTMCTL_short0 &= ~(0x01); // end short system timer
          }
          else if (system_switch_input() && (GPTMCTL_short0 & 0x01)) { // System switch pressed and short system timer on
            if (GPTMRIS_short0 & 0x01) { // if timer has ended
              GPTMICR_short0 = 0x01;
              GPTMCTL_short0 &= ~(0x01);
              GPTMICR_long = 0x01;
              GPTMCTL_long = 0x0;
              state = stop;
              break;
            }
          }
          break;

        case stop:
          LCD_StopState();
          xPos = Touch_ReadX();
          yPos = Touch_ReadY();
          if (!(GPTMCTL_long & 0x01)) { // start 5 sec timer
            start_long_timer();
          }
          else {
            if ((GPTMRIS_long & 0x01)) { // timer ended
              GPTMICR_long = 0x01;
              GPTMCTL_long &= ~(0x01);
              GPTMICR_short0 = 0x01;
              GPTMCTL_short0 &= ~(0x01);
              state = go;
              break;
            }
          } 
          
          if (system_switch_input() && !(GPTMCTL_short0 & 0x01)) { // System switch pressed and Short system timer off
            start_short0_timer();
          }
          else if (!system_switch_input() && (GPTMCTL_short0 & 0x01)) { // System switch not pressed and short system timer on
            GPTMCTL_short0 &= ~(0x01);
          }
          else if (system_switch_input() && (GPTMCTL_short0 & 0x01)) { // System switch pressed and short system timer on
            if (GPTMRIS_short0 & 0x01) { // if timer has ended
              GPTMICR_short0 = 0x01;
              GPTMCTL_short0 &= ~(0x01);
              state = start;
              break;
            }
          }
          break;
        
        case warn:
          xPos = Touch_ReadX();
          yPos = Touch_ReadY();
          LCD_WarnState();
          if (system_switch_input() && !(GPTMCTL_short0 & 0x01)) { // System switch pressed and Short system timer off
            start_short0_timer();
          }
          else if (!system_switch_input() && (GPTMCTL_short0 & 0x01)) { // System switch not pressed and short system timer on
            GPTMCTL_short0 &= ~(0x01);
          }
          else if (system_switch_input() && (GPTMCTL_short0 & 0x01)) { // System switch pressed and short system timer on
            if (GPTMRIS_short0 & 0x01) { // if timer has ended
              GPTMICR_short0 = 0x01;
              GPTMCTL_short0 &= ~(0x01);
              state = start;
              break;
            }
          }
          
          if (!(GPTMCTL_long & 0x01)) { // start 5 sec timer
            start_long_timer();
          }
          else {
            if (GPTMRIS_long & 0x01) { // timer ended
              GPTMICR_long = 0x01;
              GPTMCTL_long &= ~(0x01);
              state = stop;
            }
          }
          break;
        
        case go:
          xPos = Touch_ReadX();
          yPos = Touch_ReadY();
          LCD_GoState();
          if (system_switch_input() && !(GPTMCTL_short0 & 0x01)) { // System switch pressed and Short system timer off
            start_short0_timer();
          }
          else if (!system_switch_input() && (GPTMCTL_short0 & 0x01)) { // System switch not pressed and short system timer on
            GPTMCTL_short0 &= ~(0x01);
            printf("x\n");
          }
          else if (system_switch_input() && (GPTMCTL_short0 & 0x01)) { // System switch pressed and short system timer on
            if (GPTMRIS_short0 & 0x01) { // if timer has ended
              GPTMICR_short0 = 0x01;
              GPTMCTL_short0 &= ~(0x01);
              printf("y\n");
              state = start;
              break;
            }
          }
          
          if ((pedestrian_switch_input() == 0x2) && !(GPTMCTL_short1 & 0x01)) { // Pedestrian switch pressed and Short pedestrian timer off
            start_short1_timer();
          }
          else if ((pedestrian_switch_input() != 0x2) && (GPTMCTL_short1 & 0x01)) { // Pedestrian switch not pressed and short Pedestrian timer on
            GPTMCTL_short1 &= ~(0x01);
          }
          else if (pedestrian_switch_input() && (GPTMCTL_short1 & 0x01)) { // Pedestrian switch pressed and short pedestrian timer on
            if (GPTMRIS_short1 & 0x01) { // if timer has ended 
              GPTMICR_short1 = 0x01;
              GPTMCTL_short1 &= ~(0x01);
              GPTMICR_long = 0x01;
              GPTMCTL_long &= 0x01;
              state = warn;
              start_long_timer();
              break;
            }
          }
          
          if (!(GPTMCTL_long & 0x01)) {
            start_long_timer();
          }
          else {
            if (GPTMRIS_long & 0x01) {
              GPTMICR_long = 0x01;
              GPTMCTL_long &= 0x01;
              state = stop;
            }
          }     
          break;
      }
    }
    return 0;
}

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void Timer_long_init(void) {
    volatile unsigned short delay = 0; 
    RCGCTIMER |= 0x01; // Enable timer 0
    delay++;
    delay++;
    GPTMCTL_long = 0x0; // Disable timer
    GPTMCFG_long = 0x00000000; // 32 bit
    GPTMTAMR_long = 0x2; // Set Timer A to Periodic 
    GPTMTAMR_long &= ~0x10; // Set Timer A to count down
}

void Timer_short0_init(void) {
    volatile unsigned short delay = 0; 
    RCGCTIMER |= 0x02; // Enable timer 1
    delay++;
    delay++;
    GPTMCTL_short0 = 0x0; // Disable timer
    GPTMCFG_short0 = 0x00000000; // 32 bit
    GPTMTAMR_short0 = 0x2; // Set Timer A to Periodic 
    GPTMTAMR_short0 &= ~0x10; // Set Timer A to count down
}

void Timer_short1_init(void) {
    volatile unsigned short delay = 0; 
    RCGCTIMER |= 0x04; // Enable timer 1
    delay++;
    delay++;
    GPTMCTL_short1 = 0x0; // Disable timer
    GPTMCFG_short1 = 0x00000000; // 32 bit
    GPTMTAMR_short1 = 0x2; // Set Timer A to Periodic 
    GPTMTAMR_short1 &= ~0x10; // Set Timer A to count down
}

void start_short0_timer(void) {  
  GPTMTAILR_short0 = 0x1E84800; // Load 32000000 to achieve a 2 second delay
  GPTMCTL_short0 = 0x1; // Enable timer
}

void start_short1_timer(void) {  
  GPTMTAILR_short1 = 0x1E84800; // Load 32000000 to achieve a 2 second delay
  GPTMCTL_short1 = 0x1; // Enable timer
}

void start_long_timer(void) {  
  GPTMTAILR_long = 0x4C4B400; // Load 80000000 to achieve a 5 second delay
  GPTMCTL_long = 0x1; // Enable timer
}

void LCD_StartState(void) {
  LCD_ColorFill(0x0);
  LCD_DrawFilledCircle(60, 50, 30, ((0x55>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3));
  LCD_DrawFilledCircle(260, 50, 30, ((0x55>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3));
  LCD_DrawCircle(60, 200, 30, ((0xFF>>3)<<11) | ((0x55>>2)<<5) | (0x55>>3));
  LCD_DrawCircle(260, 200, 30, ((0x55>>3)<<11) | ((0xFF>>2)<<5) | (0x55>>3));
  LCD_DrawCircle(160, 200, 30, ((0xFF>>3)<<11) | ((0xFF>>2)<<5) | (0x55>>3));
}

void LCD_StopState(void) {
  LCD_ColorFill(0x0);
  LCD_DrawFilledCircle(60, 50, 30, ((0x55>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3));
  LCD_DrawFilledCircle(260, 50, 30, ((0x55>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3));
  LCD_DrawFilledCircle(60, 200, 30, ((0xFF>>3)<<11) | ((0x55>>2)<<5) | (0x55>>3));
}

void LCD_GoState(void) {
  LCD_ColorFill(0x0);
  LCD_DrawFilledCircle(60, 50, 30, ((0x55>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3));
  LCD_DrawFilledCircle(260, 50, 30, ((0x55>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3));
  LCD_DrawFilledCircle(260, 200, 30, ((0x55>>3)<<11) | ((0xFF>>2)<<5) | (0x55>>3));
}

void LCD_WarnState(void) {
  LCD_ColorFill(0x0);
  LCD_DrawFilledCircle(60, 50, 30, ((0x55>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3));
  LCD_DrawFilledCircle(260, 50, 30, ((0x55>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3));
  LCD_DrawFilledCircle(160, 200, 30, ((0xFF>>3)<<11) | ((0xFF>>2)<<5) | (0x55>>3));
}

unsigned long system_switch_input(void) {
  //printf("xPos is %d\n", xPos);
  //printf("yPos is %d\n", yPos);
  if (xPos < 2000 && yPos > 1500) {
    return 0x1;
  }
  else {
    return 0;
  } // 0x1 (pressed) or 0 (not pressed);
}

unsigned long pedestrian_switch_input(void) {
  //printf("xPos is %d\n", xPos);
  //printf("yPos is %d\n", yPos);
  if (xPos > 2000 && yPos > 1500) {
    return 0x2;
  }
  else {
    return 0;
  } // 0x2 (pressed) or 0 (not pressed);
}