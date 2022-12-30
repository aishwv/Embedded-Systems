/*
Aishwarya Venkatesh
1966425
12/04/2022
This is a header file for Lab4Task1c_Inits that contains pointers to registers that are 
frequently used in Lab4Task1c_Inits to set up and use the PLL
*/

#ifndef _PLL_HEADER_H_
#define _PLL_HEADER_H_

#include <stdint.h>

// ******************** CLOCK CONTROL REGISTERS ********************** //
#define MOSCCTL                 (*(volatile uint32_t *) 0x400FE07C)
#define RIS                     (*(volatile uint32_t *) 0x400FE050)
#define RSCLKCFG                (*(volatile uint32_t *) 0x400FE0B0)
#define PLLFREQ0                (*(volatile uint32_t *) 0x400FE160)
#define PLLFREQ1                (*(volatile uint32_t *) 0x400FE164)
#define PLLSTAT                 (*(volatile uint32_t *) 0x400FE168)
#define MEMTIM0                 (*(volatile uint32_t *) 0x400FE0C0)

#endif  // _PLL_HEADER_H_