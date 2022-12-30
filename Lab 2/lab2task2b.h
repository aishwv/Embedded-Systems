/*
Aishwarya Venkatesh
1966425
11/03/2022
This is a header file for main2b that contains pointers to registers that are 
frequently used in the main program along with the function prototypes of the
functions in the main program.
*/

#ifndef __HEADER1_H__           //Header guard
#define __HEADER1_H__ 
 
// REGISTER DEFINITIONS
// Registers to set up and change the data for Port N and J
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
#define GPIODIR_J    (*((volatile uint32_t *)0x40060400)) 
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIODEN_J    (*((volatile uint32_t *)0x4006051C)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC)) 
#define GPIODATA_J   (*((volatile uint32_t *)0x400603FC))
#define GPIOLOCK_J   (*((volatile uint32_t *)0x40060520))
#define GPIOCR_J     (*((volatile uint32_t *)0x40060524))
#define GPIOPUR_J    (*((volatile uint32_t *)0x40060510)) 
#define GPIOIM_J     (*((volatile uint32_t *)0x40060410)) 
#define GPIOICR_J    (*((volatile uint32_t *)0x4006041C)) 
#define GPIOMIS_J    (*((volatile uint32_t *)0x40060418)) 

// To set up and change timer 0
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL      (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG      (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR     (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR    (*((volatile uint32_t *)0x40030028))
#define GPTMRIS      (*((volatile uint32_t *)0x4003001C))
#define GPTMICR      (*((volatile uint32_t *)0x40030024))
#define GPTMIMR      (*((volatile uint32_t *)0x40030018))
#define EN0          (*((volatile uint32_t *)0xE000E100))
#define EN1          (*((volatile uint32_t *)0xE000E104))

// FUNCTION PROTOTYPES
// Sets up the LEDs
void GPIO_init(void);

// Sets up the timer 0
void Timer_init(void);

// Handles timer 0 interrupts
void Timer0A_Handler(void);
 
#endif //__HEADER1_H__ 