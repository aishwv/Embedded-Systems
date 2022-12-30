/*
Aishwarya Venkatesh
1966425
10/20/2022
This is a header file for main1a.c that contains pointers to registers that are
frequently used in the main program to enable and change data for Ports F and N.
*/

#ifndef __HEADER1_H__           // Header guard
#define __HEADER1_H__ 

// REGISTER DEFINITIONS
// Registers to set up and change the data for Port F and N
#define RCGCGPIO     (*((volatile uint32_t *)0x400FE608)) 
#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400)) 
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C)) 
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC)) 
 
#endif //__HEADER1_H__ 