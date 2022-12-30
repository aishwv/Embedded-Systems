/*
Aishwarya Venkatesh
1966425
10/20/2022
This program flashes the on board LEDs in a infinite sequential order such that 
D4 is flashed followed by D3 being flashed followed by D2 being flashed and D1
being flashed.
*/

#include <stdint.h> 
#include "lab1.h" 
 
int main(void) 
{ 
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x1020;  // Enable PortF and PortN GPIO 
    delay++;           // Delay 2 more cycles before access Timer registers 
    delay++;           // Refer to Page. 756 of Datasheet for info 
 
    GPIODIR_F = 0x11;   // Set PF0 and PF4 to output 
    GPIODIR_N = 0x03;   // Set PN0 and PN1 to output 
    GPIODEN_F = 0x11;   // Set PF0 and PF4 to digital port 
    GPIODEN_N = 0x03;   // Set PN0 and PN1 to digital port 
 
    while (1) {
    
      GPIODATA_F = 0x01;  // Set PF0 to 1
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_F = 0x00;  // Set PF0 to 0
      GPIODATA_F = 0x10;  // Set PF4 to 1
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_F = 0x00;  // Set PF4 to 0
      GPIODATA_N = 0x01;  // Set PN0 to 1
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_N = 0x00;  // Set PN0 to 0
      GPIODATA_N = 0x02;  // Set PN1 to 1
      for (int j = 0; j < 1000000; j++) {}
      GPIODATA_N = 0x00;  // Set PN1 to 0
    
    } 
 
    return 0; 
} 