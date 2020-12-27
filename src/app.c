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

volatile uint16_t LED1_PERIOD_MS = 1000;
volatile uint16_t LED2_PERIOD_MS = 100;
//uint8_t LED3_PERIOD_MS = 100;
//uint8_t LED4_PERIOD_MS = 100;

/* variables used to control pwm on led 4 */
uint8_t pwmDuty = 50;
uint8_t pwmDir = 1;

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

	static uint16_t countLED1=0,countLED2=0;

	/* toggle the leds when period is matched*/
	if(countLED1 == LED1_PERIOD_MS/2){
		LED_TOGGLE_STATE(LED1_PORT,LED1_PIN);
		countLED1=0;
		//UARTSendString("\nTICK...\n\r");
	}
	/*if(countLED2 == LED2_PERIOD_MS/2){
		LED_TOGGLE_STATE(LED2_PORT,LED2_PIN);
		countLED2=0;

	}*/

	/* update the count variables */
	countLED1++;
	countLED2++;
	
	return;
}

void PWMUpdateTask(void){

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

