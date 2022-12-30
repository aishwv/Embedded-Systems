/*
Aishwarya Venkatesh
1966425
10/20/2022
This program implements a traffic light system built with 2 off board push 
buttons and 3 LEDs depicting stop, warn and go states. There is a System On/Off 
button that turns on and off the whole system. There is also a Pedestrian button
that tells the system to go the warn state followed by the stop state if it is
go state.
*/

#include <stdint.h> 
#include "lab1.h" 
 
enum states{start, wait_on, wait_off, stop, warn, go} state;

int main(void) {
    LED_init();
    extern_switch_init();
    state = start;
    while (1) {      
      switch(state) { 
        case start:
          Red_LED_off();
          Yellow_LED_off();
          Green_LED_off();
          for (int j = 0; j < 1000000; j++) {
            if (system_switch_input() == 0x1) {
              state = wait_on;
              break;
            }   
          }                 
          break;
        
        case wait_on:  
          while (system_switch_input() == 0x1) {}
          state = stop;
          break;
          
        case wait_off:
          while (system_switch_input() == 0x1) {}
          state = start;
          break;
          
        case stop:
          Red_LED_on();
          Yellow_LED_off();
          Green_LED_off();
          state = go;          
          for (int j = 0; j < 1000000; j++) {
            if (system_switch_input() == 0x1) {
              state = wait_off;
              break;
            }          
          }          
          
          break;
        
        case warn:
          Red_LED_off();
          Yellow_LED_on();
          Green_LED_off();
          for (int j = 0; j < 1000000; j++) {
            if (system_switch_input() == 0x1) {
                state = wait_off;
                break;
            }
          }
          state = stop;
          break;
        
        case go:
          Red_LED_off();
          Yellow_LED_off();
          Green_LED_on();
          state = stop;
          for (int j = 0; j < 1000000/2; j++) {
            if (system_switch_input() == 0x1) {
              state = wait_off;
              break;
            }
            else if (pedestrian_switch_input() == 0x2) {
              state = warn;
              break;
            } 
          }
          break;
      }
    }
    return 0;
}

void LED_init(void) 
{ 
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x400;              // activate clock for Port L 
    delay++; 
    delay++; 
 
    GPIOAMSEL_L &= ~0x1C;          // disable analog function of PL4, PL3, and PL2
    GPIODIR_L |= 0x1C;             // set PL4, PL3, and PL2 to output 
    GPIOAFSEL_L &= ~0x1C;          // set PL4, PL3, and PL2 regular port function 
    GPIODEN_L |= 0x1C;             // enable digital output on PL4, PL3, and PL2 
} 
 
// turn on Red LED connected to PL4 
void Red_LED_on(void) 
{ 
    GPIODATA_L |= 0x04; 
} 
 
// turn off Red LED connected to PL4 
void Red_LED_off(void) 
{ 
    GPIODATA_L &= ~0x04; 
} 
 
// turn on Yellow LED connected to PL3 
void Yellow_LED_on(void) 
{ 
    GPIODATA_L |= 0x08; 
} 
 
// turn off Yellow LED connected to PL3
void Yellow_LED_off(void) 
{ 
    GPIODATA_L &= ~0x08; 
} 

// turn on Green LED connected to PL2 
void Green_LED_on(void) 
{ 
    GPIODATA_L |= 0x10; 
} 
 
// turn off Green LED connected to PL2
void Green_LED_off(void) 
{ 
    GPIODATA_L &= ~0x10; 
} 

void extern_switch_init(void)  
{ 
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x400;   // Enable Port L Gating Clock 
    delay++; 
    delay++; 
    GPIOAMSEL_L &= ~0x3;  // Disable PL1 and PL0 analog function 
    GPIOAFSEL_L &= ~0x3;  // Select PL1 and PL0 regular port function 
    GPIODIR_L &= ~0x3;    // Set PL1 and PL0 to input direction 
    GPIODEN_L |= 0x3;     // Enable PL1 and PL0 digital function 
} 
 
unsigned long system_switch_input(void) 
{ 
  return (GPIODATA_L & 0x1); // 0x1 (pressed) or 0 (not pressed);
}

unsigned long pedestrian_switch_input(void) 
{ 
  return (GPIODATA_L & 0x2); // 0x2 (pressed) or 0 (not pressed);
}