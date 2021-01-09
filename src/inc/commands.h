/* ****************************************************************************
 * This is the header file for various commands supported by the tm4c terminal
 * deo application
 *
 * Author:		Ameya Phadke
 * Date created:	4th Jan 2021
 * Last modified:	8th Jan 2021
 *
 * ****************************************************************************/

#ifndef _COMMANDS_H
#define _COMMANDS_H


/* number of commands implemented */
#define cmdLen 3


/* ******************************************************************************
 * This function implements the "led2" command
 *
 * param: arg pointer to the argument passed from the terminal
 *
 * return: void
 * 
 * brief: This function implements the "led2" command. Depending on the argument
 * received from the user it turns the led connected to port N pin 0,
 * on or off. Arguments are case sensitive.
 *
 * Valid arguments:
 * 1. on:	turns the led on
 * 2. off:	turns the led off
 *
 * *******************************************************************************/
void led2Command(char *arg);


/* *********************************************************************************
 * This function implements the "pwm" command
 *
 * param: arg pointer to the argument passed from the terminal
 *
 * return: void
 * 
 * brief: This function implements the "pwm" command. Depending on the argument
 * received from the user the function updates the variables for changing the
 * brightness of the led on port F pin 0. Change is brightness is achieved 
 * through changing the duty cyle of the pwm signal. The function updates the
 * appropriate variables which are monitored by pwm update Task that changes the
 * pwm duty cycle. a fade animation is also supported. Arguments are case sensitive.
 *
 * Valid arguments:
 * 1. fade:			starts the fading animation
 * 2. xx (duty in %):	updates the duty cycle percentage.
 *
 * *********************************************************************************/
void pwmCommand(char *arg);


/* ****************************************************************************
 * This function implements the "blink" command
 *
 * param: arg pointer to the argument passed from the terminal
 *
 * return: void
 * 
 * brief: This function implements the "blink" command. Depending on the argument
 * received from the user it starts or stops the blinking of the led connected 
 * to port N pin 1. It can also change the blinking period in ms.
 *
 * Valid arguments:
 * 1. on:	turns the blinking of led on
 * 2. off:	turns the blinking of led off
 * 3. period xx: sets the period of blinking in ms (minimum period needs to be
 *  the system tick period. Max period is the overflow value of 16 bit counter 
 *  for the system frequency in use.)
 *
 * ****************************************************************************/
void blinkCommand(char *arg);

#endif


