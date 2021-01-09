/* *************************************************************
 * This is the header file for declaration of terminal related
 * functions. This module works with ek-tm4c129exl and the on
 * chip UART
 *
 * Author:		Ameya Phadke
 * Date created:	19th Dec 2020
 * Last modified:	8th Jan 2021
 *
 * ************************************************************/


#ifndef _TERMINAL_H
#define _TERMINAL_H



/* ******************************************************************************
 * This function adds the string to be sent to the terminal to the output buffer
 *
 * param: s		pointer to the string to be sent to terminal output. 
 * return: int	return -1 if buffer is full else 0 is returned.
 * 
 * brief: This function adds the string to be sent to terminal to output buffer.
 * It also acts as a level of abstraction between uart module and terminal task.
 *
 * ******************************************************************************/
int terminalSendString(char * s);



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
void terminalBackgroundTask(void);



/* *********************************************************************************
 * This function initializes the terminal interface
 *
 * param: void 
 * return: void
 * 
 * brief: This function initializes the terminal interface
 *
 * *********************************************************************************/
void terminalInit(void);



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
void terminalUpdateTask(void);


#endif


