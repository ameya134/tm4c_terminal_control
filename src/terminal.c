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

uint8_t dutyVal;
char dutyStr[5];

void terminalInit(void){

	UARTSendString("\n\rConnected to TM4C terminal....\n\r");

	UARTSendString("LED 4 PWM DUTY: ");

	dutyVal = PWMGetDuty();

	convertIntToString(dutyVal,dutyStr);

	UARTSendString(dutyStr);
	UARTSendString("\n\r");

	return;
}
