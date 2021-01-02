/* *************************************************************
 * This is the header file for declaration of terminal related
 * functions. This module works with ek-tm4c129exl and the on
 * chip UART
 *
 * Engineer:	Ameya Phadke
 * Date:	19th Dec 2020
 *
 * ************************************************************/


#ifndef _TERMINAL_H
#define _TERMINAL_H

void terminalInit(void);
void terminalUpdateTask(void);
void terminalBackgroundTask(void);
#endif
