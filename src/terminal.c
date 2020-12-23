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
#define CMD_BUF_LEN 64

char terminalIpCmdBuf[CMD_BUF_LEN];
char terminalRecvChar;
uint8_t bufLen = 0;

void terminalInit(void){

	UARTSendString("\n\rConnected to TM4C terminal....\n\r");

	UARTSendString("LED 4 PWM DUTY: ");

	dutyVal = PWMGetDuty();

	convertIntToString(dutyVal,dutyStr);

	UARTSendString(dutyStr);
	UARTSendString("\n\r");
	UARTSendString("terminal@TM4C: >");
	
	return;
}

void terminalUpdateTask(void){

	terminalRecvChar = UARTRecvChar();
	
	terminalEcho();
	if((terminalRecvChar == '\r') | (bufLen == CMD_BUF_LEN -3))
	{
		terminalIpCmdBuf[bufLen] = '\n';
		terminalIpCmdBuf[bufLen+1] = '\r';
		terminalIpCmdBuf[bufLen+2] = '\0';

		UARTSendString("\n\r");
		UARTSendString(terminalIpCmdBuf);
		UARTSendString("terminal@TM4C: >");
		bufLen = 0;
	}
	else if(terminalRecvChar >= 0x20){
		terminalIpCmdBuf[bufLen] = (char )terminalRecvChar;
		bufLen ++;
	}

	
	return;
}

void terminalEcho(void){

	UARTSendChar(terminalRecvChar);
	return;
}
