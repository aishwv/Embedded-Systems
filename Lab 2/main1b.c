/*
Aishwarya Venkatesh
1966425
11/03/2022
This program implements a traffic light system built with 2 off board push 
buttons and 3 LEDs depicting stop, warn and go states. There is a System On/Off 
button that turns on and off the whole system. There is also a Pedestrian button
that tells the system to go the warn state followed by the stop state if it is
go state.
*/

#include <stdint.h> 
#include "lab2task1b.h" 

enum states{start, stop, warn, go} state;

int main(void) {
    printf("hello");
    LED_init();
    Timer_long_init();
    Timer_short0_init();
    Timer_short1_init();
    extern_switch_init();
    state = start;
    while (1) {
      switch(state) { 
        case start:
          Red_LED_off();
          Yellow_LED_off();
          Green_LED_off();
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
          Red_LED_on();
          Yellow_LED_off();
          Green_LED_off();
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
          Red_LED_off();
          Yellow_LED_on();
          Green_LED_off();
          
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
          Red_LED_off();
          Yellow_LED_off();
          Green_LED_on();
          
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