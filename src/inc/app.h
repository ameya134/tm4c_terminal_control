/* Header file for application related code
 *
 * Engineer: 	Ameya Phadke
 * Date:	4th Dec 2020 
 *
 * ________________________________________*/

#ifndef _APP_H
#define _APP_H


/* ***************************************************************************
 * This function performs necessary initialization for the application
 *
 * param: void
 *
 * return: void
 * 
 * brief: The function initializes the hardware required by the application
 * Function needs to be called before the main function enteres into whlie(1)
 * superloop.
 *
 * **************************************************************************/
void appTaskInit(void);


/* ***************************************************************************
 * This task is executed periodically. called from SysTick handler
 *
 * param: void
 * 
 * return: void
 * 
 * brief: This task is called by SysTick ISR on every system tick. the function
 * calls the tasks that need to be performed at regular intervals.
 *
 * **************************************************************************/
void mainAppTask(void);


/* ***************************************************************************
 * This task updates the blinking led.
 *
 * param: void
 *
 * return: void
 * 
 * brief: This task controlles and updates the blinkin behaviour of led.
 * according to commands given from the terminal the task blinks the led with
 * desired period and can also stop the blinking.
 *
 * **************************************************************************/
void LEDUpdateTask(void);


/* *****************************************************************************
 * This task updates pwm output connected to led
 *
 * param: void
 *
 * return: void
 * 
 * brief: This task controlles and updates the pwm output connected to led.
 * based on commands given from terminal it changes the brightness of led by
 * controlling the duty of pwm cycle. It can also render a fading animation on
 * the led based on user commands from terminal.
 *
 * ****************************************************************************/
void PWMUpdateTask(void);


#endif


