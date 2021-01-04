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

/* character received from uart is stored here*/
char recvVar;



/* ******************************************************
 *
 * void appTaskInit void
 * this function initializes all the peripherals
 * specifically required by the application 
 *
 * ******************************************************/
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



/* ******************************************************
 * 
 * void mainAppTask void
 * This task is periodically called by the 
 * SysTick_Handler after system tick interval
 * this is where main code is executed
 *
 * ******************************************************/
void mainAppTask(void){


	LEDUpdateTask();

	PWMUpdateTask();

	terminalUpdateTask();


	return;
}


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

