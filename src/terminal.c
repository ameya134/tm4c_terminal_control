/* ****************************************************
 * This is the source code for terminal application
 * which runs uses UART for connection
 *
 * Engineer:		Ameya Phadke
 * Date created:	19th Dec 2020
 * Last modified:	8th Jan 2021
 *
 * ***************************************************/

#include "main.h"
#include "mystring.h"

#include "bsp.h"
#include "uart.h"
#include "pwm.h"

#include "terminal.h"
#include "commands.h"



/* variables and array to hold the commands received 
 * from the UART terminal */
#define CMD_BUF_LEN 64

char terminalIpCmdBuf[CMD_BUF_LEN];
char terminalRecvChar;
uint8_t bufLen = 0;

extern char *commandsList[];



/* This FIFO buffer stores pointers to all strings that
 * are to be printed on the terminal by the backgroun task. */
#define ioBufCapacity 100

struct FIFO{
	uint8_t firstLoc;
	uint8_t lastLoc;
	uint8_t bufLen;
	
	char *buffer[ioBufCapacity];
} terminalOutputBuffer;




/* Implementation of private private functions */


/* ****************************************************************************
 * This function initializes FIFO buffer
 *
 * param: void
 * return: void
 * 
 * brief: This function initializes FIFO buffer
 *
 * ****************************************************************************/
void terminalIOBufInit(void){

	terminalOutputBuffer.firstLoc = 0;
	terminalOutputBuffer.lastLoc = 0;
	terminalOutputBuffer.bufLen = 0;

}




/* ****************************************************************************
 * This function returns the a byte of data received by the uart module
 *
 * param: void 
 * return: char	byte of data received by uart module
 * 
 * brief: This function returns the a byte of data received by the uart module
 *
 * ****************************************************************************/
char terminalGetChar(void){

	return UARTRecvChar();
}



/* ********************************************************************************
 * This function echos the character received, back to the terminal output
 *
 * param: void 
 * return: void
 * 
 * brief: This function echos the character received, back to the terminal output
 *
 * *******************************************************************************/
void terminalEcho(void){

	if(terminalRecvChar == '\b')
		return;
	terminalSendString(&terminalRecvChar);
	return;
}



/* *********************************************************************************
 * This function updates the input buffer used to parse the commands according
 * to characters received by the uart module.
 *
 * param: void 
 * return: void
 * 
 * brief: This function updates the input buffer used to parse the commands 
 * according to characters received by the uart module. It formats the input buffer
 * to separate any commands and arguments by replacing ' ' with '\0'
 *
 * *********************************************************************************/
void inputBufferUpdate(void){

	if((terminalRecvChar == '\r') | (bufLen == CMD_BUF_LEN -3)){
		/* terminate the string when 'enter' is received */
		terminalIpCmdBuf[bufLen] = '\0';
		bufLen = 0;
	}
	else if((bufLen > 0) && (terminalRecvChar == '\b')){
		/* update the terminal for 'backspace' */
		bufLen--;
		terminalSendString("\b \b");
	}
	else if(terminalRecvChar == ' '){
		/* replace ' ' by '\0' to separate arguments */
		terminalIpCmdBuf[bufLen] = '\0';
		bufLen++;
	}
	else if(terminalRecvChar >= 0x20){
		
		terminalIpCmdBuf[bufLen] = terminalRecvChar;
		bufLen ++;
	}

	return;
}



/* *********************************************************************************
 * This function parses the command entered at terminal
 *
 * param: void 
 * return: int 	index of command if there is a match, otherwise -1
 * 
 * brief: This function parses the command entered at terminal. It compares the 
 * command entered at terminal to the list of implemented commands.
 *
 * *********************************************************************************/
int terminalCommandParse(void){

	int i;

	for(i=0;i<cmdLen;i++){
		if(strCmp(terminalIpCmdBuf,commandsList[i],-1) == 0)
			return i;
		
	}

	return -1;
}



/* Implementation of public functions */



/* ******************************************************************************
 * This function adds the string to be sent to the terminal to the output buffer
 *
 * param: s		pointer to the string to be sent to terminal output. 
 * return: int	return -1 if buffer is full else 0 is returned.
 * 
 * brief: This function adds the string to be sent to terminal to output buffer.
 * It also acts as a level of abstraction between uart module and terminal task.
 *
 * *****************************************************************************/
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



/* *********************************************************************************
 * This is a background task which send output buffer data through uart.
 *
 * param: void 
 * return: void
 * 
 * brief: This is a background task which keeps sending any pending data in the
 * output buffer. task is called from while(1) superloop in the main and can be 
 * preempted by the SysTick handler.
 *
 * *********************************************************************************/
void terminalBackgroundTask(void){

	/* keep sending data until buffer is empty */
	while(terminalOutputBuffer.bufLen != 0){

		UARTSendString(terminalOutputBuffer.buffer[
				terminalOutputBuffer.firstLoc]);

		/* update buffer indices */
		terminalOutputBuffer.firstLoc ++;
		if(terminalOutputBuffer.firstLoc == ioBufCapacity){
			terminalOutputBuffer.firstLoc = 0;
		}
		terminalOutputBuffer.bufLen--;
	}


	return;
}




/* *********************************************************************************
 * This function initializes the terminal interface
 *
 * param: void 
 * return: void
 * 
 * brief: This function initializes the terminal interface
 *
 * *********************************************************************************/
char dutyStr[5];
void terminalInit(void){

	terminalIOBufInit();

	terminalSendString("\n\rWELCOME\n\r");
	terminalSendString("\n\rConnected to TM4C terminal....\n\r");

	terminalSendString("LED 4 PWM DUTY: ");

	convertIntToString(PWMGetDuty(),dutyStr);

	terminalSendString(dutyStr);
	terminalSendString("\n\r");
	terminalSendString(commandsList[0]);
	terminalSendString("\n\r");
	terminalSendString("terminal@TM4C: >");
	
	return;
}



/* *********************************************************************************
 * This is the periodic terminal update task 
 *
 * param: void 
 * return: void
 * 
 * brief: This task is called periodically by the mainAppTask. It updates the I/O
 * buffers for the terminal. command parser is also called from here.
 *
 * *********************************************************************************/
void terminalUpdateTask(void){

	/* check if new charater is present */
	terminalRecvChar = terminalGetChar();
	
	/* echo the new data */
	terminalEcho();
	
	/* update the input buffer */
	inputBufferUpdate();

	/* if command is entered parse the buffer data
	 * to call appropriate command */
	if(terminalRecvChar == '\r'){
		switch(terminalCommandParse()){
			
			case 0:	led2Command(&terminalIpCmdBuf[5]);
					break;
	
			case 1: blinkCommand(&terminalIpCmdBuf[6]);
					break;

			case 2: pwmCommand(&terminalIpCmdBuf[4]);
					break;
		}

		terminalSendString("\n\r");
		terminalSendString("terminal@TM4C: >");
		
		/* clear input buffer*/
		
		int i;
		for(i=0;i<CMD_BUF_LEN;i++){
			terminalIpCmdBuf[i] = 0;
		}

	}

	return;
}


