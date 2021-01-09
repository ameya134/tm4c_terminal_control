/* *****************************************************************************
 * This source file implements various commands supported by the tm4c terminal
 * demo application.
 *
 * Author:		Ameya Phadke
 * Date created:	4th Jan 2021
 * Last modified:	8th Jan 2021
 *
 * *****************************************************************************/

#include "main.h"
#include "mystring.h"

#include "bsp.h"
#include "pwm.h"

#include "commands.h"
#include "terminal.h"



/* list of all the commands */
char *commandsList[] = {"led2",
	"blink",
	"pwm"};



/* ****************************************************************************
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
 * ****************************************************************************/
void led2Command(char *arg){
	
	if(strCmp(arg,"on",-1) == 0){
		LED_TURN_ON(LED2_PORT,LED2_PIN);
		terminalSendString("\n\rLED 2 turned ON");
	}
	else if(strCmp(arg,"off",-1) == 0){
		LED_TURN_OFF(LED2_PORT,LED2_PIN);
		terminalSendString("\n\rLED 2 turned OFF");
	}
	else{
		terminalSendString("\n\rINVALID ARGUMENT");
	}

	return;
}



/* **********************************************************************************
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

/* arrays and variables needed by the function */
char dutyStr[2];
extern volatile int pwm_fade;
extern volatile int8_t pwmDuty;

void pwmCommand(char *arg){

	if(strCmp(arg,"fade",-1) == 0){
		pwm_fade = 1;
	}
	else{
		/* turn off the fade */
		pwm_fade = 0;
		
		terminalSendString("\n\rPWM duty Updated: ");
		pwmDuty = (uint8_t)convertStringToInt(arg);
		
		if(pwmDuty > 100){
			pwmDuty = 100;
		}
		convertIntToString(pwmDuty,dutyStr);
		terminalSendString(dutyStr);

		terminalSendString("%\n\r");
	}

	return;
}



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

/* variables used to pass data to the led task */
extern volatile int blink_on;
extern volatile uint16_t LED1_PERIOD_MS;
volatile uint16_t countLED1;

void blinkCommand(char *arg){

	if(strCmp(arg,"on",-1) == 0){
		blink_on = 1;
	}
	else if(strCmp(arg,"off",-1) == 0){
		blink_on = 0;
	}
	else if(strCmp(arg,"period",-1) == 0){
		LED1_PERIOD_MS = (uint16_t) convertStringToInt(&arg[7]);
		countLED1 = 0;
		terminalSendString("\n\rblinking period updated\n\r");
	}

	return;
}


