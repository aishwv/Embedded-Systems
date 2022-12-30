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
#include "lab2task2c.h" 

enum states{start, stop, warn, go} state;

volatile uint32_t sys_flag = 0;
volatile uint32_t ped_flag = 0;

int main(void) {
    LED_init();
    Red_LED_off();
    Yellow_LED_off();
    Green_LED_off();
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
          break;

        case stop:
          Red_LED_on();
          Yellow_LED_off();
          Green_LED_off();
          if (GPTMCTL_long != 0x01) {
            GPTMCTL_long |= 0x01;   
            GPTMICR_long |= 0x01;
          }
          break;
        
        case warn:
          Red_LED_off();
          Yellow_LED_on();
          Green_LED_off();
          if (GPTMCTL_long != 0x01) {
            GPTMCTL_long |= 0x01;   
            GPTMICR_long |= 0x01;
          }
          break;
        
        case go:
          Red_LED_off();
          Yellow_LED_off();
          Green_LED_on();
          if (GPTMCTL_long != 0x01) {
            GPTMCTL_long |= 0x01;   
            GPTMICR_long |= 0x01;
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
    RCGCTIMER |= 0x01; // Enable timer 0A
    delay++;
    delay++;
    GPTMCTL_long = 0x0; // Disable timer 0A
    GPTMCFG_long = 0x00000000; // Set timer 0A to 32 bit
    GPTMTAMR_long = 0x2; // Set Timer 0A to Periodic 
    GPTMTAMR_long &= ~0x10; // Set Timer 0A to count down
    GPTMTAILR_long = 0x4C4B400; // Load 80000000 to achieve a 5 second delay
    GPTMIMR_long |= 0x01; // Enable timer 0A interrupts
    EN0 |= 0x00080000; // Enable interrupt register 19
}

void Timer_short0_init(void) {
    volatile unsigned short delay = 0; 
    RCGCTIMER |= 0x02; // Enable timer 1A
    delay++;
    delay++;
    GPTMCTL_short0 = 0x0; // Disable timer 1A
    GPTMCFG_short0 = 0x00000000; // Set timer 1A to 32 bit
    GPTMTAMR_short0 = 0x2; // Set Timer 1A to Periodic 
    GPTMTAMR_short0 &= ~0x10; // Set Timer 1A to count down
    GPTMTAILR_short0 = 0x1E84800; // Load 32000000 to achieve a 2 second delay
    GPTMIMR_short0 |= 0x01; // Enable timer 1A interrupts
    EN0 |= 0x00200000; // Enable interrupt register 21
}

void Timer_short1_init(void) {
    volatile unsigned short delay = 0; 
    RCGCTIMER |= 0x04; // Enable timer 2A
    delay++;
    delay++;
    GPTMCTL_short1 = 0x0; // Disable timer 2A
    GPTMCFG_short1 = 0x00000000; // Set timer 2A to 32 bit
    GPTMTAMR_short1 = 0x2; // Set Timer 2A to Periodic 
    GPTMTAMR_short1 &= ~0x10; // Set Timer 2A to count down
    GPTMTAILR_short1 = 0x1E84800; // Load 32000000 to achieve a 2 second delay
    GPTMIMR_short1 |= 0x01; // Enable timer 2A interrupts
    EN0 |= 0x00800000; // Enable interrupt register 23
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
    GPIOIS_L &= ~0x3; // Set interrupt to edge mode
    GPIOIBE_L = 0x3;  // Set interrupt mode to both edges
    GPIOICR_L |= 0x3; // Clear interrupt
    GPIOIM_L |= 0x03; 
    
    EN1 |= 0x00200000;
} 
 
unsigned long system_switch_input(void) 
{ 
  return (GPIODATA_L & 0x1); // 0x1 (pressed) or 0 (not pressed);
}

unsigned long pedestrian_switch_input(void) 
{ 
  return (GPIODATA_L & 0x2); // 0x2 (pressed) or 0 (not pressed);
}

void Timer0A_Handler(void) {
  if (GPTMCTL_long & 0x01) {   
    if (GPTMRIS_long & 0x01) {
      GPTMICR_long |= 0x01;
      GPTMCTL_long &= ~(0x01);
      GPTMICR_short0 |= 0x01;
      GPTMCTL_short0 &= ~(0x01);
      GPTMICR_short1 |= 0x01;
      GPTMCTL_short1 &= ~(0x01);
      GPIOICR_L |= 0x03;
    }
  }
  switch(state) {
  case stop:
    state = go;
    break;
  case warn:
    state = stop;
    break;
  case go:
    state = stop;
    break;
  default:
    break;
  }
}

void Timer1A_Handler(void) {
  if ((GPTMCTL_short0 & 0x01) && (sys_flag == 1)) { //short timer on and sys pressed    
    if (GPTMRIS_short0 & 0x01) {
      GPTMICR_short0 |= 0x01;
      GPTMCTL_short0 &= ~(0x01);
      GPTMICR_long |= 0x01;
      GPTMCTL_long &= ~(0x01);
    }
  }
  switch(state) {
  case start:
    state = stop;
    break;
  case stop:
    state = start;
    break;
  case warn:
    state = start;
    break;
  case go:
    state = start;
    break;
  default:
    break;
  }
}

void Timer2A_Handler(void) {
  if ((GPTMCTL_short1 & 0x01) && (ped_flag == 1)) { //short timer on and ped pressed    
    if (GPTMRIS_short1 & 0x01) {
      GPTMICR_short1 |= 0x01;
      GPTMCTL_short1 &= ~(0x01);
      GPTMICR_long |= 0x01;
      GPTMCTL_long &= 0x01;
    }
  }
  switch(state) {
  case go:
    state = warn;
    break;
  default:
    break;
  }
}

void Switch_Handler(void) {
  if (!sys_flag && (GPIORIS_L & 0x01)) {
    sys_flag = 1;
    GPIOICR_L |= 0x01;
  }
  else if (sys_flag && (GPIORIS_L & 0x01)) {
   sys_flag = 0;
   GPIOICR_L |= 0x01;
  }
  if (!ped_flag && (GPIORIS_L & 0x02)) {
    ped_flag = 1;
    GPIOICR_L |= 0x02;
  }
  else if (ped_flag && (GPIORIS_L & 0x02)) {
   ped_flag = 0;
   GPIOICR_L |= 0x02;
  }
  if ((GPTMCTL_short0 != 0x01) && (sys_flag == 1)) { //short timer off and sys pressed
    GPTMCTL_short0 |= 0x01;
  }
  if ((GPTMCTL_short1 != 0x01) && (ped_flag == 1)) { //short timer off and ped pressed
    GPTMCTL_short1 |= 0x01;
  }
}