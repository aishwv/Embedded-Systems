/*
Aishwarya Venkatesh
1966425
11/03/2022
This is a header file for main2b that contains pointers to registers that are 
frequently used in the main program along with the function prototypes of the
functions in the main program.
*/

#ifndef __HEADER1_H__           // Header guard
#define __HEADER1_H__ 

// REGISTER DEFINITIONS
// Registers to set up and change the data for Port F and N
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 

#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400)) 
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C)) 
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC)) 

#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC)) 

// To set up and change the timers
#define RCGCTIMER    (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL      (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG      (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR     (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR    (*((volatile uint32_t *)0x40030028))
#define GPTMRIS      (*((volatile uint32_t *)0x4003001C))
#define GPTMICR      (*((volatile uint32_t *)0x40030024))

// FUNCTION PROTOTYPE
// Sets up the LEDs
void GPIO_init(void);

// Sets up the timer
void Timer_init(void);

// Polls the timer
void GPTM_poll(void);
 
#endif //__HEADER1_H__ 