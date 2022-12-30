/*
Aishwarya Venkatesh
1966425
10/20/2022
This program turns on the D1 on board LED whenever the SW1 on board switch is 
pressed, and turns on the D2 whenever SW2 on board switch is pressed.
*/

#include <stdint.h> 
#include "lab1.h" 
 
int main(void) 
{ 
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x1100;  // Enable PortJ and PortN GPIO 
    delay++;           // Delay 2 more cycles before access Timer registers 
    delay++;           // Refer to Page. 756 of Datasheet for info 
 
    GPIODIR_N = 0x03;   // Set PN0 and PN1 to output 
    GPIODIR_J = 0x0;   // Set PJ0 and PJ1 to input 
    
    GPIOPUR_J |= 0x03; //
    
    GPIODEN_N = 0x03;   // Set PN0 and PN1 to digital port 
    GPIODEN_J = 0x03;   // Set PJ0 and PJ1 to digital port 
     
    while (1) {
      if (GPIODATA_J == 0x00) {
        GPIODATA_N = 0x03;
      }
      else if (GPIODATA_J == 0x01) {
        GPIODATA_N = 0x01;
      }
      else if (GPIODATA_J == 0x02) {
        GPIODATA_N = 0x02;
      }
      else if (GPIODATA_J == 0x03) {
        GPIODATA_N = 0x00;
      }
    }
 
    return 0; 
} 