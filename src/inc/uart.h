/* ********************************************************
 * This is the header file for UART functions declarations
 *
 * Engineer: Ameya Phadke
 * Date:	4th Dec 2020
 *
 * ********************************************************/

#ifndef _UART_H
#define _UART_H


void UARTInit(uint32_t baudrate);
void UARTSendChar(char c);
uint8_t UARTRecvChar(void);
void UARTSendString(char *s);
void UARTPrintNumToString(uint32_t num);

#endif
