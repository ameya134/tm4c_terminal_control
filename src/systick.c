/* This file implements the functions related to
 * SysTick timer initialization and use
 *
 * Engineer: 	Ameya Phadke
 * Date: 	4th Dec 2020
 *
 * ______________________________________________*/

#include "main.h"
#include "tm4c129encpdt.h"
#include "bsp.h"
#include "app.h"

void SysTickIntEnable(uint16_t period_ms){

	NVIC_ST_RELOAD_R = (uint32_t) (SYSCLOCK_16MHz /1000) * period_ms;

	/* set the following bits 
	 * bit 0: enables and starts the timer in multishot mode
	 * bit 1: enables interrupt for when timer counts to 0
	 * bit 2: sets the clock source as system clock */
	
	NVIC_ST_CTRL_R |= (uint32_t)((0x1<<2) | (0x1<<1) | (0x1<<0));
}


void SysTick_Handler(void){

	/* main application task is called from here */
	mainAppTask();

	return;
}
