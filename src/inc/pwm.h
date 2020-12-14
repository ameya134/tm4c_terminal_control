/* ********************************************************
 * This file provides the funciton prototypes for 
 * configuration and use of pwm module which is present on
 * tm4c129encpdt 
 *
 * Engineer: 	Ameya Phadke
 * Date:	13th Dec 2020
 *
 * ********************************************************/


#ifndef _PWM_H
#define _PWM_H


/*
 * void PWMLedInit (uint32_t period, uint8_t duty)
 *
 * period: period of the pwm in microseconds
 * duty: duty cycle in percentage
 *
 * configures the PWM module and the LED GPIO pin
 * connected on port F pin 0 on board ek-tm4c129exl
 *
 * */
void PWMLedInit(uint32_t period, uint8_t duty);



/*
 * void PWMLedDutyUpdate (uint8_t duty)
 *
 * duty: percentage duty cycle
 *
 * updates the duty cycle of the pwm on
 * the clock cycle the counter reaches zero
 *
 * */
void PWMLedDutyUpdate(uint8_t duty);



#endif
