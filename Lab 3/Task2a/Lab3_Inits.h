/*
Aishwarya Venkatesh
1966425
11/29/2022
This is a header file for Lab3_Inits that contains function prototypes of the 
functions in the main program
*/

#ifndef _Lab3_Inits_H_
#define _Lab3_Inits_H_

// FUNCTION PROTOTYPES
// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency {PRESET1 = 120, PRESET2 = 60, PRESET3 = 12};

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes the 2 onboard switches.
void Switch_Init(void);

// Initializes ADC Module 0 Sample Sequencer 3. The module is triggered by
// Timer module 0 subtimer A at 1 HZ. The interupt of ADC0 SS3 will be
// generated whenever the A/D conversion is done.
void ADCReadPot_Init(void);

// Initializes Timer 0A to trigger ADC0 at 1 HZ.
void TimerADCTriger_Init(void);

// Initializes UART2
void UART_Init(void);

#endif  // _Lab3_Inits_H_