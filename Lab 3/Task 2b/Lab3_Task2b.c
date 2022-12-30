/*
Aishwarya Venkatesh
1966425
11/29/2022
This program implements a “Return-to-Sender” function that receives a single
character via UART and immediately transmits back the character that it 
receives.
*/

#include <stdint.h>
#include <stdio.h>
#include "Lab3_Inits.h"

#include "lab3task2b.h"

int main(void){
  UART_Init();
  while(1) {    
    char c = readChar();
    printChar(c);
  }
  return 0;
}

// Reads the character from PuTTy
char readChar(void){
  char c;  
  while ((UARTFR & (1 << 4)) != 0){}
  c = (char)UARTDR;
  return c;
}

// Prints character to PuTTy
void printChar(char c){
  while((UARTFR & (1 << 5)) != 0);
  UARTDR = c;
}

