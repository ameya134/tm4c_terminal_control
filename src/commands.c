/* ****************************************************
 * This is the source code for terminal application
 * which runs uses UART for connection
 *
 * Engineer:	Ameya Phadke
 * Date:		4th Jan 2021
 *
 * ***************************************************/

#include "main.h"
#include "mystring.h"

#include "bsp.h"
#include "pwm.h"

#include "commands.h"
#include "terminal.h"

char *commandsList[] = {"led2",
						"blink",
						"pwm"};

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



char dutyStr[2];
extern volatile int pwm_fade;

void pwmCommand(char *arg){

	if(strCmp(arg,"fade",-1) == 0){
		pwm_fade = 1;
	}
	else{
		/* turn off the fade */
		pwm_fade = 0;
		
		terminalSendString("\n\rPWM duty Updated: ");
		PWMLedDutyUpdate( (uint8_t)convertStringToInt(arg) );

		convertIntToString(PWMGetDuty(),dutyStr);
		terminalSendString(dutyStr);

		terminalSendString("%\n\r");
	}

	return;
}


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
