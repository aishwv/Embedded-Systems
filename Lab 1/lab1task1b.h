/*
Aishwarya Venkatesh
1966425
10/20/2022
This is a header file for main1a.c that contains pointers to registers that are
frequently used in the main program to enable and change data for Ports N and J.
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
#define GPIOPUR_J    (*((volatile uint32_t *)0x40060510)) 
 
#endif //__HEADER1_H__ 