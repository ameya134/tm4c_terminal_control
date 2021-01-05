/* *********************************************************************
 * This file implements the functions related to
 * SysTick timer initialization and use
 *
 * Engineer: 	Ameya Phadke
 * Date: 	4th Dec 2020
 *
 * *********************************************************************/

#include "main.h"
#include "tm4c129encpdt.h"
#include "bsp.h"
#include "app.h"



/* ****************************************************************
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
 * ****************************************************************/
void SysTickIntEnable(uint16_t period_ms){

	NVIC_ST_RELOAD_R = (uint32_t) (SYSCLOCK_Hz /1000) * period_ms;

	/* set the following bits 
	 * bit 0: enables and starts the timer in multishot mode
	 * bit 1: enables interrupt for when timer counts to 0
	 * bit 2: sets the clock source as system clock */
	
	NVIC_ST_CTRL_R |= (uint32_t)((0x1<<2) | (0x1<<1) | (0x1<<0));
}



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
void SysTick_Handler(void){

	/* main application task is called from here */
	mainAppTask();

	return;
}


