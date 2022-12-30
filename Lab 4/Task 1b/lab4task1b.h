/*
Aishwarya Venkatesh
1966425
12/04/2022
This is a header file for Lab4Task1b_Inits and Lab4_Task1b that contains pointers to 
registers that are frequently used in the main program to set up and use the ADC
and GPIO
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

#include <stdint.h>

// REGISTER DEFINITIONS
// Register to set up and change the ADC module
#define RCGCADC                 (*(volatile uint32_t *) 0x400FE638)
#define ADCCC                   (*(volatile uint32_t *) 0x40038FC8)
#define GPIOAFSEL_E             (*(volatile uint32_t *) 0x4005C420)
#define GPIODEN_E               (*(volatile uint32_t *) 0x4005C51C)
#define GPIOAMSEL_E             (*(volatile uint32_t *) 0x4005C528)
#define ADCACTSS                (*(volatile uint32_t *) 0x40038000)
#define ADCEMUX                 (*(volatile uint32_t *) 0x40038014)
#define ADCSSMUX3               (*(volatile uint32_t *) 0x400380A0)
#define ADCSSCTL3               (*(volatile uint32_t *) 0x400380A4)
#define ADCSSFIFO3              (*(volatile uint32_t *) 0x400380A8)
#define ADCIM                   (*(volatile uint32_t *) 0x40038008)
#define EN0                     (*(volatile uint32_t *) 0xE000E100)
#define ADCISC                  (*(volatile uint32_t *) 0x4003800C)

// Registers to set up and change the data for Port J and Port A
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 

#define GPIODIR_J    (*((volatile uint32_t *)0x40060400)) 
#define GPIODEN_J    (*((volatile uint32_t *)0x4006051C)) 
#define GPIODATA_J   (*((volatile uint32_t *)0x400603FC)) 
#define GPIOLOCK_J   (*((volatile uint32_t *)0x40060520))
#define GPIOCR_J     (*((volatile uint32_t *)0x40060524))
#define GPIOPUR_J    (*((volatile uint32_t *)0x40060510)) 

#define GPIODEN_A    (*((volatile uint32_t *)0x4005851C))
#define GPIOAFSEL_A  (*((volatile uint32_t *)0x40058420))
#define GPIOPCTL_A   (*((volatile uint32_t *)0x4005852C))

// To set up and change the timer 0
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL      (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG      (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR     (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR    (*((volatile uint32_t *)0x40030028))
#define GPTMICR      (*((volatile uint32_t *)0x40030024))
#define GPTMADCEV    (*((volatile uint32_t *)0x40030070))


#endif  // __HEADER1_H__