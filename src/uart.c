/* ********************************************************************
 * This file contains the implementation of functions to send
 * data using the UART 0. compatible with TI's tivaware microcontroller
 * header file
 *
 * Engineer: 	Ameya Phadke
 * Date:	4th Dec 2020
 *
 * ********************************************************************/

#include "main.h"
#include "tm4c129encpdt.h"

#include "uart.h"


/* ********************************************************************
 * The following function initializes the all the
 * necessary gpio and UART module settings to use UART
 *
 * baud rate is calculated using following formula
 *
 * BRD = BRDI + BRDF = UARTsysclk / (clkdiv * baudrate)
 *
 * where BRDI is the 16 bit integer part and BRDF is the
 * 6 bit fractional part
 *
 * *******************************************************************/

void UARTInit(uint32_t baudrate){

	/* Enable the power to UART Module and appropriate GPIO port*/

	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
	while(!(SYSCTL_PRUART_R & SYSCTL_PRUART_R0));

	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
	while(!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0));

	/* enable DEN and AFSEL for PA0 and PA1 */
	GPIO_PORTA_AHB_DEN_R	|= ((1U<<1) | (1U<<0));
	GPIO_PORTA_AHB_AFSEL_R	|= ((1U<<1) | (1U<<0));

	/* Enable slew rate control for the gpio port pins
	 * 
	 * Set 4bit field in GPIOPCTL reg for tx, rx pins*/
	GPIO_PORTA_AHB_DR2R_R	|= ((1U<<1) | (1U<<0));
	GPIO_PORTA_AHB_PCTL_R	|= ((0x01<<4) | (0x01<<0));
	

	/* set the UART control register and baudrate
	 * first we disable the UART then set the parameters
	 * then reenable the UART
	 *
	 * set bit 9 for Rx enable
	 * set bit 8 for Tx enable
	 * set bit 7 for loopback enable
	 * set bit 0 for UART enable*/

	/* disable UART temporarily*/
	UART0_CTL_R &= ~(1U<<0);

	UART0_CTL_R |= ((1U<<9) | (1U<<8));// | (1U<<7));

	UART0_IBRD_R = (uint32_t) SYSCLOCK_16MHz / (16 * baudrate);
	//float temp = 0.425347;
	UART0_FBRD_R = (uint32_t) 44;//((temp *64) + 0.5);

	UART0_LCRH_R |= (0x03<<5);

	UART0_CC_R |= (0x00<<0);

	/* enable UART */
	UART0_CTL_R |= (1U<<0);
}


void UARTSendChar(char c){
	UART0_DR_R = c;
}

uint8_t UARTRecvChar(void){

	if((UART0_FR_R & (1U<<6))){
		return ((uint8_t) UART0_DR_R);
	}
	return 0;
}

void UARTSendString(char *s){


}
