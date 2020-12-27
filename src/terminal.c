/* ****************************************************
 * This is the source code for terminal application
 * which runs uses UART for connection
 *
 * Engineer:	Ameya Phadke
 * Date: 	19th Dec 2020
 *
 * ***************************************************/

#include "main.h"
#include "mystring.h"

#include "terminal.h"
#include "bsp.h"
#include "uart.h"
#include "pwm.h"

/* Declaration for private functions */
void terminalEcho(void);
void inputBufferUpdate(void);
int terminalCommandParse(void);

uint8_t dutyVal;
char dutyStr[5];

/* variables and array to hold the commands received 
 * from the UART terminal */
#define CMD_BUF_LEN 64

char terminalIpCmdBuf[CMD_BUF_LEN];
char terminalRecvChar;
uint8_t bufLen = 0;

#define cmdLen 3
char *commandsList[] = { "led2 on",
			"led2 off",
			"cmd3"};

void terminalInit(void){

	UARTSendString("\n\rConnected to TM4C terminal....\n\r");

	UARTSendString("LED 4 PWM DUTY: ");

	dutyVal = PWMGetDuty();

	convertIntToString(dutyVal,dutyStr);

	UARTSendString(dutyStr);
	UARTSendString("\n\r");
	UARTSendString(commandsList[0]);
	UARTSendString("\n\r");
	UARTSendString("terminal@TM4C: >");
	
	return;
}

void terminalUpdateTask(void){

	terminalRecvChar = UARTRecvChar();
	
	terminalEcho();
	
	inputBufferUpdate();

	if(terminalRecvChar == '\r'){
		switch(terminalCommandParse()){
			
			case 0:	LED_TURN_ON(LED2_PORT,LED2_PIN);
				UARTSendString("\n\rLED 2 turned ON");
				break;

			case 1: LED_TURN_OFF(LED2_PORT,LED2_PIN);
				UARTSendString("\n\rLED 2 turned OFF");
				break;
			
			case 2: UARTSendString("\n\rcmd3 received\n\r");
		}

		UARTSendString("\n\r");
		UARTSendString("terminal@TM4C: >");
	}

	return;
}

void terminalEcho(void){

	if(terminalRecvChar == '\b')
		return;
	UARTSendChar(terminalRecvChar);
	return;
}

void inputBufferUpdate(void){

	if((bufLen > 0) && (terminalRecvChar == '\b')){
		bufLen--;
		UARTSendString("\b \b");
	}
	else if((terminalRecvChar == '\r') | (bufLen == CMD_BUF_LEN -3))
	{
		terminalIpCmdBuf[bufLen] = '\0';

		bufLen = 0;
		
	}
	else if(terminalRecvChar >= 0x20){
		terminalIpCmdBuf[bufLen] = (char )terminalRecvChar;
		bufLen ++;
	}

	return;
}

int terminalCommandParse(void){

	int i;

	for(i=0;i<cmdLen;i++){
		if(strCmp(terminalIpCmdBuf,commandsList[i]) == 0)
			return i;
		
	}

	return -1;
}
