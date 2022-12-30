/*
Aishwarya Venkatesh
1966425
11/03/2022
This program flashes the on board LEDs in a infinite sequential order such that 
D4 is flashed followed by D3 being flashed followed by D2 being flashed and D1
being flashed.
*/

#include <stdint.h> 
#include "lab2task2a.h" 
#include <stdio.h>

volatile uint32_t flag = 0;
 
int main(void) 
{   
    GPIO_init();
    Timer_init();
    flag = 0;
    while (1) {
      switch(flag%4){
      case 0:
        GPIODATA_N = 0x00;  // Set PN1 to 0
        GPIODATA_F = 0x01;  // Set PF0 to 1
        break;
        
      case 1:
        GPIODATA_F = 0x00;  // Set PF0 to 0
        GPIODATA_F = 0x10;  // Set PF4 to 1
        break;
        
      case 2:
        GPIODATA_F = 0x00;  // Set PF4 to 0
        GPIODATA_N = 0x01;  // Set PN0 to 1
        break;
        
      case 3:
        GPIODATA_N = 0x00;  // Set PN0 to 0
        GPIODATA_N = 0x02;  // Set PN1 to 1
        break;
      }
    } 
 
    return 0; 
}

void GPIO_init(void) {
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x1020;  // Enable PortF and PortN GPIO 
    delay++;           // Delay 2 more cycles before access Timer registers 
    delay++;           // Refer to Page. 756 of Datasheet for info
 
    GPIODIR_F = 0x11;   // Set PF0 and PF4 to output 
    GPIODIR_N = 0x03;   // Set PN0 and PN1 to output 
    GPIODEN_F = 0x11;   // Set PF0 and PF4 to digital port 
    GPIODEN_N = 0x03;   // Set PN0 and PN1 to digital port 
}

void Timer_init(void) {
    volatile unsigned short delay = 0; 
    RCGCTIMER |= 0x01; // Enable timer 0A
    delay++;
    delay++;
    GPTMCTL = 0x0; // Disable timer 0A
    GPTMCFG = 0x00000000; // Set Timer 0A to 32 bit
    GPTMTAMR = 0x2; // Set Timer 0A to Periodic 
    GPTMTAMR &= ~0x10; // Set Timer 0A to count down
    GPTMTAILR = 0xF42400; // Load 16000000 to achieve a 1 Hz blink rate
    GPTMIMR |= 0x01; // Enable interrupts on Timer 0A
    EN0 = 0x00080000; // Enable Interrupt register 19
    GPTMCTL = 0x1; // Enable timer 0A
}

void Timer0A_Handler(void) {
  flag++;
  GPTMICR |= 0x01; // Clear GPTMRIS bit 0
  GPTMCTL |= 0x01; // Enable timer 0A
}