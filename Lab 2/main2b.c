/*
Aishwarya Venkatesh
1966425
11/03/2022
This program blinks LED 1 and when SW1 is pressed it shines the LED2 and turns 
off LED1. When SW2 pressed when LED2 is shining, LED2 goes off and turns on LED1 
again.
*/

#include <stdint.h> 
#include "lab2task2b.h" 

volatile uint32_t flag = 0;

enum states{blink, on} state;
 
int main(void) 
{
    GPIO_init();
    Timer_init();
    flag = 0;
    state = blink;
    while (1) {
      switch(state) {
      case blink:
        switch(flag) {
        case 0:
          GPIODATA_N = 0x00;
          break;
        case 1:
          GPIODATA_N = 0x02;
          break;
        }
        break;
      case on:
        GPIODATA_N = 0x01;
        break;
      }
    }
 
    return 0; 
} 

void GPIO_init(void) {    
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x1100;  // Enable PortJ and PortN GPIO 
    delay++;           // Delay 2 more cycles before access Timer registers 
    delay++;           // Refer to Page. 756 of Datasheet for info 
 
    GPIODIR_N = 0x03;   // Set PN0 and PN1 to output 
    GPIODIR_J = 0x0;   // Set PJ0 and PJ1 to input 
    
    GPIOLOCK_J = 0x4C4F434B; // Unlocks GPIOCR
    GPIOCR_J = 0x03; // Enables GPIOPUR to be written
    GPIOPUR_J |= 0x03; // Switch config
    GPIOIM_J = 0x03; // Enable PJ0 and PJ1 interrupt mask
    
    GPIODEN_N = 0x03;   // Set PN0 and PN1 to digital port 
    GPIODEN_J = 0x03;   // Set PJ0 and PJ1 to digital port
}

void Timer_init(void) {
    volatile unsigned short delay = 0; 
    RCGCTIMER |= 0x01; // Enable timer 0
    delay++;
    delay++;
    GPTMCTL = 0x0; // Disable timer
    GPTMCFG = 0x00000000; // 32 bit
    GPTMTAMR = 0x2; // Set Timer A to Periodic 
    GPTMTAMR &= ~0x10; // Set Timer A to count down
    GPTMTAILR = 0xF42400; // Load 16000000 to achieve a 1 Hz blink rate
    GPTMIMR |= 0x01; // Enables timer 0A interrupts
    EN0 = 0x00080000; // Enables interrupt register 19
    EN1 = 0x00080000; // Enables interrupt register 51
    GPTMCTL = 0x1; // Enable timer
}

void Timer0A_Handler(void) {
  if (flag == 0) { // off
    flag++;
  }
  else { // on
    flag = 0;
  }
  GPTMICR |= 0x01;
  GPTMCTL |= 0x01; 
}

void Switch_Handler(void) {
  if (GPIOMIS_J & 0x01) { // SW1 interrupted
    state = on;
    GPIOICR_J |= 0x01;
  }
  else if (GPIOMIS_J & 0x02){ // SW2 interrupted
    state = blink;
    GPIOICR_J |= 0x02;
  }
}