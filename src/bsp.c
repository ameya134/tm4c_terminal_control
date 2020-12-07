/* This is the led driver for ek-tm4c129exl launchpad
 * this driver works with tm4c129encpdt.h provided by TI*/

#include "bsp.h"


static uint8_t ledBits=0x00; // bitwise variable

/*connected to port N pin 1*/
void INIT_LED_1(void)
{
	/* start clock to port N(12th port)*/
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R12;
	
	while(!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R12));
	
	GPIO_PORTN_DIR_R	|=	(1U<<LED1_PIN);
	GPIO_PORTN_DEN_R	|=	(1U<<LED1_PIN);
	GPIO_PORTN_DATA_R	&= ~(1U<<LED1_PIN);
	
	ledBits &= ~(1U<<LED1_PIN);
}

/*connected to port N pin 0*/
void INIT_LED_2(void)
{
	/* start clock to port N(12th port)*/
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R12;
	
	while(!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R12));
	
	GPIO_PORTN_DIR_R	|=	(1U<<LED2_PIN);
	GPIO_PORTN_DEN_R	|=	(1U<<LED2_PIN);
	GPIO_PORTN_DATA_R	&= ~(1U<<LED2_PIN);
	
	ledBits &= ~(1U<<LED2_PIN);
}

/*connected to port F pin 4*/
void INIT_LED_3(void)
{
	/* start clock to port F(5th port)*/
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	
	while(!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5));
	
	GPIO_PORTF_AHB_DIR_R	|=	(1U<<LED3_PIN);
	GPIO_PORTF_AHB_DEN_R	|=	(1U<<LED3_PIN);
	GPIO_PORTF_AHB_DATA_R	&= ~(1U<<LED3_PIN);
	
	ledBits &= ~(1U<<LED3_PIN);
}

/*connected to port F pin 0*/
void INIT_LED_4(void)
{
	/* start clock to port F(5th port)*/
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	
	while(!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5));
	
	GPIO_PORTF_AHB_DIR_R	|=	(1U<<LED4_PIN);
	GPIO_PORTF_AHB_DEN_R	|=	(1U<<LED4_PIN);
	GPIO_PORTF_AHB_DATA_R	&= ~(1U<<LED4_PIN);
	
	ledBits &= ~(1U<<LED4_PIN);
}


/* Turn on led connected to port portBase and pin pinNo*/
void LED_TURN_ON(uint8_t portBase, uint8_t pinNO)
{
	if(portBase == GPIO_PORT_N)
		GPIO_PORTN_DATA_R |= (1U<<pinNO);
	if(portBase == GPIO_PORT_F)
		GPIO_PORTF_AHB_DATA_R |= (1U<<pinNO);

	ledBits |= (1U<<LED1_PIN);
}

/* Turn off led connected to port portBase and pin pinNo*/
void LED_TURN_OFF(uint8_t portBase, uint8_t pinNO)
{
	if(portBase == GPIO_PORT_N)
		GPIO_PORTN_DATA_R &= ~(1U<<pinNO);
	if(portBase == GPIO_PORT_F)
		GPIO_PORTF_AHB_DATA_R &= ~(1U<<pinNO);

	ledBits &= ~(1U<<LED1_PIN);
}

/* toggle led connected to port portBase and pin pinNo*/
void LED_TOGGLE_STATE(uint8_t portBase, uint8_t pinNO)
{	
	if(portBase == GPIO_PORT_N)
		GPIO_PORTN_DATA_R ^= (1U<<pinNO);
	if(portBase == GPIO_PORT_F)
		GPIO_PORTF_AHB_DATA_R ^= (1U<<pinNO);

	ledBits ^= (1U<<LED1_PIN);
}
