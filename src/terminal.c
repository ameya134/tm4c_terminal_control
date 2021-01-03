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


uint8_t dutyVal;
char dutyStr[5];

/* variables and array to hold the commands received 
 * from the UART terminal */
#define CMD_BUF_LEN 64

char terminalIpCmdBuf[CMD_BUF_LEN];
char terminalRecvChar;
uint8_t bufLen = 0;

#define cmdLen 3
char *commandsList[] = {"led2",
			"cmd3",
			"pwm"};

/* This stores pointers to all strings that are to be printed
 * on the terminal by the backgroun task. */
#define ioBufCapacity 100

struct FIFO{
	uint8_t firstLoc;
	uint8_t lastLoc;
	uint8_t bufLen;
	
	char *buffer[ioBufCapacity];
} terminalOutputBuffer;


void terminalIOBufInit(void){

	terminalOutputBuffer.firstLoc = 0;
	terminalOutputBuffer.lastLoc = 0;
	terminalOutputBuffer.bufLen = 0;

}
/* Implementation of private private functions */

int terminalSendString(char * s){

	if(terminalOutputBuffer.bufLen < ioBufCapacity){
		terminalOutputBuffer.buffer[terminalOutputBuffer.lastLoc] = s;

		/* temporarily disable interrupts while updating counts*/
		//__asm("disable_irq");
		terminalOutputBuffer.lastLoc++;
		if(terminalOutputBuffer.lastLoc == ioBufCapacity){
			terminalOutputBuffer.lastLoc = 0;
		}
		terminalOutputBuffer.bufLen++;
		//__asm("enable_irq");

		return 0;
	}
	else{
		/* terminal buffer full */
		return 1;
	}
}

char terminalGetChar(void){

	return UARTRecvChar();
}

void terminalEcho(void){

	if(terminalRecvChar == '\b')
		return;
	terminalSendString(&terminalRecvChar);
	return;
}

void inputBufferUpdate(void){

	if((terminalRecvChar == '\r') | (bufLen == CMD_BUF_LEN -3)){
		
		terminalIpCmdBuf[bufLen] = '\0';
		bufLen = 0;
	}
	else if((bufLen > 0) && (terminalRecvChar == '\b')){
		
		bufLen--;
		terminalSendString("\b \b");
	}
	else if(terminalRecvChar == ' '){
		
		terminalIpCmdBuf[bufLen] = '\0';
		bufLen++;
	}
	else if(terminalRecvChar >= 0x20){
		
		terminalIpCmdBuf[bufLen] = terminalRecvChar;
		bufLen ++;
	}

	return;
}

int terminalCommandParse(void){

	int i;

	for(i=0;i<cmdLen;i++){
		if(strCmp(terminalIpCmdBuf,commandsList[i],-1) == 0)
			return i;
		
	}

	return -1;
}

void terminalBackgroundTask(void){

	while(terminalOutputBuffer.bufLen != 0){

		UARTSendString(terminalOutputBuffer.buffer[
				terminalOutputBuffer.firstLoc]);

		/* temporarily disable interrupts while updating counts */
		//__asm("disable_irq");
		terminalOutputBuffer.firstLoc ++;
		if(terminalOutputBuffer.firstLoc == ioBufCapacity){
			terminalOutputBuffer.firstLoc = 0;
		}
		terminalOutputBuffer.bufLen--;
		//__asm("enable_irq");
	}


	return;
}


/* Implementation of public functions */

void terminalInit(void){

	terminalIOBufInit();

	terminalSendString("\n\rConnected to TM4C terminal....\n\r");

	terminalSendString("LED 4 PWM DUTY: ");

	dutyVal = PWMGetDuty();

	convertIntToString(dutyVal,dutyStr);

	terminalSendString(dutyStr);
	terminalSendString("\n\r");
	terminalSendString(commandsList[0]);
	terminalSendString("\n\r");
	terminalSendString("terminal@TM4C: >");
	
	return;
}

void terminalUpdateTask(void){

	terminalRecvChar = terminalGetChar();
	
	terminalEcho();
	
	inputBufferUpdate();

	if(terminalRecvChar == '\r'){
		switch(terminalCommandParse()){
			
			case 0:	if(strCmp(&terminalIpCmdBuf[5],"on",-1) == 0){
					LED_TURN_ON(LED2_PORT,LED2_PIN);
					terminalSendString("\n\rLED 2 turned ON");
				}
				else if(strCmp(&terminalIpCmdBuf[5],"off",-1) == 0){
					LED_TURN_OFF(LED2_PORT,LED2_PIN);
					terminalSendString("\n\rLED 2 turned OFF");
				}
				else{
					terminalSendString("\n\rINVALID ARGUMENT");
				}
				break;
	
			case 1: terminalSendString("\n\rcmd3 received\n\r");
				break;

			case 2: PWMLedDutyUpdate(
					(uint8_t)convertStringToInt(&terminalIpCmdBuf[4])
					);
				terminalSendString("\n\rPWM duty Updated: ");
				char dutyStr[2];
				convertIntToString(PWMGetDuty(),dutyStr);
				terminalSendString(dutyStr);
				terminalSendString("%\n\r");
				break;
		}

		terminalSendString("\n\r");
		terminalSendString("terminal@TM4C: >");
	}

	return;
}

