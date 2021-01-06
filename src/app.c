/* ***************************************
 * MAIN APPLICATION PROGRAM RESIDES HERE 
 *
 * Engineer: 	Ameya Phadke
 * Date:	4th Dec 2020
 *
 * ***************************************/

#include "main.h"
#include "mystring.h"
#include "app.h"

#include "bsp.h"
#include "uart.h"
#include "pwm.h"
#include "terminal.h"


/* variable used to control pwm fading on led 4 */
volatile int pwm_fade = 0;

/* variables to control blinking */
volatile uint16_t LED1_PERIOD_MS = 200;
volatile int blink_on = 0;
volatile uint16_t countLED1=0;



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
void appTaskInit(void){

	INIT_LED_1();
	INIT_LED_2();


	LED_TURN_ON(LED1_PORT,LED1_PIN);
	LED_TURN_ON(LED2_PORT,LED2_PIN);

	PWMLedInit(1000U,50);

	UARTInit((uint32_t) 115200);

	terminalInit();

	return;
}


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
void mainAppTask(void){

	/* task for controlling led2 */
	LEDUpdateTask();

	/* task for controlling pwm connected to
	 * the led on port F pin 0 */
	PWMUpdateTask();

	/* updates the terminal */
	terminalUpdateTask();
	

	return;
}


/* ***************************************************************************
 * This task updates the blinking led.
 *
 * param: void
 *
 * return: void
 * 
 * brief: This task controlles and updates the blinking behaviour of led.
 * according to commands given from the terminal the task blinks the led with
 * desired period and can also stop the blinking.
 *
 * **************************************************************************/
void LEDUpdateTask(void){

	if(blink_on == 0){
		return;
	}
	/* toggle the leds when period is matched*/
	if((countLED1 == LED1_PERIOD_MS/2)){
		LED_TOGGLE_STATE(LED1_PORT,LED1_PIN);
		countLED1=0;
	}

	/* update the count variable */
	countLED1++;
	
	return;
}


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
void PWMUpdateTask(void){

	static int8_t pwmDuty = 50;
	static uint8_t pwmDir = 1;

	/* function returns if fade is disabled.
	 * fade can be enabled using the terminal command. */
	if (pwm_fade == 0){
		return;
	}
		
	/* update pwm duty cycle */
	if(pwmDir == 1){
		pwmDuty++;
	}else{
		pwmDuty--;
	}
	if((pwmDuty == 99) || (pwmDuty == 0)){
		pwmDir = ~pwmDir;
	}

	PWMLedDutyUpdate(pwmDuty);
	
	return;
}


