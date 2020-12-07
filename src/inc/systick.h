/* This is the header file for systick timer implementation
 * This file is compatible with ti's tivware microcontroller 
 * header file
 * 
 *
 * Engineer:	Ameya Phadke
 * Date:	4th Dec 2020
 *
 *
 * ________________________________________________________*/

#ifndef _SYSTICK_H
#define _SYSTICK_H


void SysTickIntEnable(uint16_t period_ms);
void SysTick_Handler(void);



#endif
