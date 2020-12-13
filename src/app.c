/* MAIN APPLICATION PROGRAM RESIDES HERE 
 *
 * Engineer: 	Ameya Phadke
 * Date:	4th Dec 2020
 *
 * ______________________________________*/

#include "main.h"
#include "bsp.h"
#include "uart.h"

volatile uint16_t LED1_PERIOD_MS = 1000;
volatile uint16_t LED2_PERIOD_MS = 100;
//uint8_t LED3_PERIOD_MS = 100;
//uint8_t LED4_PERIOD_MS = 100;


/* ******************************************************
 *
 * void appTaskInit void
 * this function initializes all the peripherals
 * specifically required by the application 
 *
 * ******************************************************/
void appTaskInit(void){

	INIT_LED_1();
	INIT_LED_2();


	LED_TURN_ON(LED1_PORT,LED1_PIN);
	LED_TURN_ON(LED2_PORT,LED2_PIN);

	UARTInit((uint32_t) 115200);
}


/* ******************************************************
 * 
 * void mainAppTask void
 * This task is periodically called by the 
 * SysTick_Handler after system tick interval
 * this is where main code is executed
 *
 * ******************************************************/
void mainAppTask(void){

	static uint16_t count1=0,count2=0;

	if(count1 == LED1_PERIOD_MS/2){
		LED_TOGGLE_STATE(LED1_PORT,LED1_PIN);
		count1=0;
		UARTSendString("\nTICK...\n\r");
	}
	if(count2 == LED2_PERIOD_MS/2){
		LED_TOGGLE_STATE(LED2_PORT,LED2_PIN);
		count2=0;

	}

	char c = UARTRecvChar();
	UARTSendChar(c);

	if( (c <= '9') & (c >= '0')){
		LED1_PERIOD_MS = (uint16_t) 10*(1 + (uint16_t)c - '0');
		UARTSendString("\nperiod updated \n\r");
	}

	count1++;
	count2++;

}
