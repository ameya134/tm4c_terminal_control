/* ***********************************************************
 * This file implements the functions used to configure and 
 * use the pwm module present on tm4c129encpdt
 * This file uses TI's provided tm4c129encpdt.h header file
 *
 * Engineer:	Ameya Phadke
 * Date:	13th Dec 2020
 *
 * ***********************************************************/

#include "tm4c129encpdt.h"
#include "main.h"

#include "pwm.h"


/*
 * void PWMLedInit (period, duty)
 * 
 * period: period of pwm wave in microseconds
 * duty: duty cycle in integer percentage
 *
 * */

void PWMLedInit(uint32_t period, uint8_t duty){


	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R0;
	while(!(SYSCTL_PRPWM_R & SYSCTL_PRPWM_R0));

	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	while(!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5));

	/* init gpio */

	GPIO_PORTF_AHB_DEN_R	|= (1U<<0);
	GPIO_PORTF_AHB_AFSEL_R	|= (1U<<0);
	GPIO_PORTF_AHB_PCTL_R	|= (0x06<<0);

	/*
	 * Init PWM 
	 * */

	PWM0_0_CTL_R |= (0x0<<0);
	PWM0_0_GENA_R |= ((0x3<<6) | (0x2<<2));

	uint32_t loadVal = (SYSCLOCK_16MHz / 1000000) * period;
	uint32_t dutyVal = (duty/100) * loadVal;

	PWM0_0_LOAD_R = loadVal;
	PWM0_0_CMPA_R = dutyVal;

	PWM0_0_CTL_R	|= (1U<<0);
	PWM0_ENABLE_R	|= (1U<<0);
	
	return;
}

void PWMLedDutyUpdate(uint8_t duty){

	PWM0_0_CMPA_R = (duty * PWM0_0_LOAD_R)/100;

	return;
}
