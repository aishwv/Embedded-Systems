/*
Aishwarya Venkatesh
1966425
11/03/2022
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
#define GPIOIS_L         (*((volatile uint32_t *)0x40062404)) 
#define GPIOIBE_L        (*((volatile uint32_t *)0x40062408))
#define GPIOIM_L         (*((volatile uint32_t *)0x40062410)) 
#define GPIOICR_L        (*((volatile uint32_t *)0x4006241C)) 
#define GPIOMIS_L        (*((volatile uint32_t *)0x40062418)) 
#define GPIORIS_L        (*((volatile uint32_t *)0x40062414)) 

// To set up and change timer 0
#define RCGCTIMER     (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_long       (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_long       (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_long      (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_long     (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_long       (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_long       (*((volatile uint32_t *)0x40030024))
#define GPTMIMR_long       (*((volatile uint32_t *)0x40030018))

// To set up and change timer 1
#define GPTMCTL_short0       (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_short0       (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_short0      (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_short0     (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_short0       (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_short0       (*((volatile uint32_t *)0x40031024))
#define GPTMIMR_short0       (*((volatile uint32_t *)0x40031018))

// To set up and change timer 2
#define GPTMCTL_short1       (*((volatile uint32_t *)0x4003200C))
#define GPTMCFG_short1       (*((volatile uint32_t *)0x40032000))
#define GPTMTAMR_short1      (*((volatile uint32_t *)0x40032004))
#define GPTMTAILR_short1     (*((volatile uint32_t *)0x40032028))
#define GPTMRIS_short1       (*((volatile uint32_t *)0x4003201C))
#define GPTMICR_short1       (*((volatile uint32_t *)0x40032024))
#define GPTMIMR_short1       (*((volatile uint32_t *)0x40032018))

// To enable interrupt registers
#define EN0          (*((volatile uint32_t *)0xE000E100))
#define EN1          (*((volatile uint32_t *)0xE000E104))

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
 
// Sets up the timer 0
void Timer_long_init(void);

// Sets up the timer 1
void Timer_short0_init(void);

// Sets up the timer 2
void Timer_short1_init(void);

// Handles timer 0 interrupts
void Timer0A_Handler(void);

// Handles timer 1 interrupts
void Timer1A_Handler(void);

// Handles timer 2 interrupts
void Timer2A_Handler(void);

#endif //__HEADER1_H__ 