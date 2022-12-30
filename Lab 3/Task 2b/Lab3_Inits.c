/*
Aishwarya Venkatesh
1966425
11/03/2022
This file initializes all the registers needed to use the UART
*/

#include "Lab3_Inits.h"
#include "lab3task2b.h"

void UART_Init(void) {
  RCGCUART |= 0x4; // Enable UART2
  RCGCGPIO |= 0x1;
  UARTCTL &= ~0x1; // Diasble the UART by clearing the UARTEN bit
  UARTIBRD |= 104; // Integer portion of BRD
  UARTFBRD |= 11; // Fraction portion of BRD
  UARTLCRH |= 0x70; // no FIFO, 8 bits,  no parity, no interrupt
  UARTCC = 0x5; // Alternate clock source as defined by ALTCLKCFG
  UARTCTL |= 0x301; // Enable TX, RX and UART2
  GPIODEN_A |= 0xC0; // Set PA6 and PA7 to digital port
  GPIOAFSEL_A |= 0xC0; // Select alterbate functions of PA6 and PA7
  GPIOPCTL_A |= 0x11000000; // Port control 0 and 1
}