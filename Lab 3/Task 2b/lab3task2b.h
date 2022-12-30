/*
Aishwarya Venkatesh
1966425
11/29/2022
This is a header file for Lab3_Task2b and Lab3_Inits that contains all the
registers needed to set up and change UART and Port A
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

#include <stdint.h>

// REGISTER DEFINITIONS
// Registers to set up and change the data for Port A
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 

#define GPIODEN_A    (*((volatile uint32_t *)0x4005851C))
#define GPIOAFSEL_A  (*((volatile uint32_t *)0x40058420))
#define GPIOPCTL_A   (*((volatile uint32_t *)0x4005852C))


// Registers to set up and change UART
#define RCGCUART     (*((volatile uint32_t *)0x400FE618))
#define UARTCTL      (*((volatile uint32_t *)0x4000E030))
#define UARTIBRD     (*((volatile uint32_t *)0x4000E024))
#define UARTFBRD     (*((volatile uint32_t *)0x4000E028))
#define UARTLCRH     (*((volatile uint32_t *)0x4000E02C))
#define UARTCC       (*((volatile uint32_t *)0x4000EFC8))
#define UARTFR       (*((volatile uint32_t *)0x4000E018))
#define UARTDR       (*((volatile uint32_t *)0x4000E000))

#endif  // __HEADER1_H__