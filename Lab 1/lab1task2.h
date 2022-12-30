/*
Aishwarya Venkatesh
1966425
10/20/2022
This is a header file for main2 that contains pointers to registers that are 
frequently used in the main program along with the function prototypes of the
functions in the main program.
*/

#ifndef __HEADER1_H__    // Header guard
#define __HEADER1_H__ 

// REGISTER DEFINITIONS
// Registers to set up and change the data for Port L
#define RCGCGPIO         (*((volatile uint32_t *)0x400FE608)) 
#define GPIOAMSEL_L      (*((volatile uint32_t *)0x40062528)) 
#define GPIODIR_L        (*((volatile uint32_t *)0x40062400)) 
#define GPIODEN_L        (*((volatile uint32_t *)0x4006251C)) 
#define GPIOAFSEL_L      (*((volatile uint32_t *)0x40062420)) 
#define GPIODATA_L       (*((volatile uint32_t *)0x400623FC)) 

// FUNCTION PROTOTYPES
// Sets up the LEDs
void LED_init(void);

// Turns on the Red LED
void Red_LED_on(void);

// Turns off the Red LED
void Red_LED_off(void);

// Turns on the Yellow LED
void Yellow_LED_on(void);

// Turns off the Yellow LED
void Yellow_LED_off(void);

// Turns on the Green LED
void Green_LED_on(void);

// Turns off the Green LED
void Green_LED_off(void);

// Sets up the switches
void extern_switch_init(void);

// Gets the value of input given by the system on/off push button 
unsigned long system_switch_input(void);

// Gets the value of input given by the pedestrian push button 
unsigned long pedestrian_switch_input(void);
 
#endif //__HEADER1_H__ 