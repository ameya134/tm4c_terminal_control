/* *******************************************************************
 * This is the header file for systick timer implementation
 * This file is compatible with ti's tivware microcontroller 
 * header file
 * 
 *
 * Author:		Ameya Phadke
 * Date created:	4th Dec 2020
 * Last modified:	8th Jan 2021
 *
 * *******************************************************************/

#ifndef _SYSTICK_H
#define _SYSTICK_H


/* ********************************************************************
 * This function initializes the SysTick Timer
 *
 * param: period_ms	time period in ms between every timer interrupt
 *
 * return: void
 * 
 * brief: This function configures and enables the systick timer to 
 * generate priodic interrupts according to period_ms parameter.
 * the reload value is calculated using the SYSCLOCK_Hz macro
 * which specifies system frequency in Hertz.
 * 
 * following formula is used for calculation
 *
 * Reload_val = (system_frequency/1000) * period_ms 
 *
 * ********************************************************************/
void SysTickIntEnable(uint16_t period_ms);



/* ***************************************************************
 * This is the Interrupt Service Routine (ISR) for the
 * SysTick Interrupt.
 *
 * param void
 * return void
 * 
 * brief: This is the interrupt handler that is called by SysTick
 * interrupt. All the tasks that need to be called periodically
 * are called from here. The mainAppTask is called every time the
 * interrupt is raised. Thus all the functions inside mainAppTask
 * are executed on a periodic basis.
 *
 * **************************************************************/
void SysTick_Handler(void);



#endif

