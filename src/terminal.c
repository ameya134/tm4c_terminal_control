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
#include "uart.h"
#include "pwm.h"

/* Declaration for private functions */
void terminalEcho(void);


uint8_t dutyVal;
char dutyStr[5];

/* variables and array to hold the commands received 
 * from the UART terminal */
char terminalIpCmdBuf[100];
char terminalRecvChar;
uint8_t bufLen = 0;

void terminalInit(void){

	UARTSendString("\n\rConnected to TM4C terminal....\n\r");

	UARTSendString("LED 4 PWM DUTY: ");

	dutyVal = PWMGetDuty();

	convertIntToString(dutyVal,dutyStr);

	UARTSendString(dutyStr);
	UARTSendString("\n\r");

	return;
}

void terminalUpdateTask(void){

	terminalRecvChar = UARTRecvChar();
	
	terminalEcho();
	if(terminalRecvChar == '\r')
	{
		terminalIpCmdBuf[bufLen] = '\n';
		UARTSendString(terminalIpCmdBuf);
		bufLen = 0;
	}
	else if(terminalRecvChar >= 0x20){
		terminalIpCmdBuf[bufLen] = terminalRecvChar;
		bufLen ++;
	}

	
	return;
}

void terminalEcho(void){

	UARTSendChar(terminalRecvChar);
	return;
}
