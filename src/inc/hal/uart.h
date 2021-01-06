/* ********************************************************
 * This is the header file for UART functions declarations
 *
 * Engineer: Ameya Phadke
 * Date:	4th Dec 2020
 *
 * ********************************************************/

#ifndef _UART_H
#define _UART_H


/* ***************************************************************************
 * This function initializes the UART module
 *
 * param: baudrate	rate in bits/sec at which uart will send and receive data
 *
 * return: void
 * 
 * brief: The following function initializes the all the necessary gpio and 
 * UART module settings to use UART
 *
 * baud rate is calculated using following formula
 *
 * BRD = BRDI + BRDF = UARTsysclk / (clkdiv * baudrate)
 *
 * where BRDI is the 16 bit integer part and BRDF is the
 * 6 bit fractional part
 *
 * **************************************************************************/
void UARTInit(uint32_t baudrate);


/* ***************************************************************************
 * This function receives a byte of data through UART module
 *
 * param: void
 *
 * return: uint8_t return a byte of data received from uart module
 * 
 * brief: The function return a byte of data received by the UART module on
 * the Rx pin of the microcontroller. A value of 0x00 is returned if no new
 * data is available.
 *
 * **************************************************************************/
uint8_t UARTRecvChar(void);


/* ******************************************************************************
 * This function sends a byte of data through UART module
 *
 * param: c	the byte of data that needs to be sent
 *
 * return: void
 * 
 * brief: The functions sends a byte of data through uart module when an ongoing
 * transmission if any is completed.
 *
 * *****************************************************************************/
void UARTSendChar(char c);


/* ******************************************************************************
 * This function sends a byte of data through UART module
 *
 * param: c	the byte of data that needs to be sent
 *
 * return: void
 * 
 * brief: The functions sends a byte of data through uart module when an ongoing
 * transmission if any is completed.
 *
 * *****************************************************************************/
void UARTSendString(char *s);


/* **********************************************************************************
 * This function sends a BASE 10 character representation of an integer through UART.
 *
 * param: num	The number that is to be sent through UART.
 *
 * return: void
 * 
 * brief: This function sends the BASE 10 character representation of an integer.
 * This function relies on a function which is used to convert integer into string.
 *
 * *********************************************************************************/
void UARTPrintNumToString(uint32_t num);

#endif


