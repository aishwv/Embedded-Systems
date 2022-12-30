/*
Aishwarya Venkatesh
1966425
12/04/2022
This is a header file for main2a that contains pointers to registers that are 
frequently used in the main program along with the function prototypes of the
functions in the main program.
*/

#ifndef __HEADER1_H__    // Header guard
#define __HEADER1_H__ 

enum frequency {PRESET1 = 120, PRESET2 = 60, PRESET3 = 12};

// REGISTER DEFINITIONS
// To set up and change the timer 0
#define RCGCTIMER     (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_long       (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_long       (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_long      (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_long     (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_long       (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_long       (*((volatile uint32_t *)0x40030024))

// To set up and change the timer 1
#define GPTMCTL_short0       (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_short0       (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_short0      (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_short0     (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_short0       (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_short0       (*((volatile uint32_t *)0x40031024))

// To set up and change the timer 2
#define GPTMCTL_short1       (*((volatile uint32_t *)0x4003200C))
#define GPTMCFG_short1       (*((volatile uint32_t *)0x40032000))
#define GPTMTAMR_short1      (*((volatile uint32_t *)0x40032004))
#define GPTMTAILR_short1     (*((volatile uint32_t *)0x40032028))
#define GPTMRIS_short1       (*((volatile uint32_t *)0x4003201C))
#define GPTMICR_short1       (*((volatile uint32_t *)0x40032024))


// FUNCTION PROTOTYPES 
// Sets up Timer 0
void Timer_long_init(void);

// Sets up Timer 1
void Timer_short0_init(void);

// Sets up Timer 2
void Timer_short1_init(void);

// Starts the 2 second Timer 1
void start_short0_timer(void);

// Starts the 2 second Timer 2
void start_short1_timer(void);

// Starts the 5 second Timer 0
void start_long_timer(void);

// Initializes PLL modules to specified frequency
int PLL_Init(enum frequency freq);

// Displays the start state on the LCD
void LCD_StartState(void);

// Displays the stop state on the LCD
void LCD_StopState(void);

// Displays the go state on the LCD
void LCD_GoState(void);

// Displays the warn state on the LCD
void LCD_WarnState(void);

// Reads touch and returns 0x1 if virtual button is pressed
unsigned long system_switch_input(void);

// Reads touch and return 0x2 if virtual button is pressed
unsigned long pedestrian_switch_input(void);

#endif //__HEADER1_H__ 