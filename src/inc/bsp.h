#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include "tm4c129encpdt.h"

#define GPIO_PORT_N 12
#define GPIO_PORT_F 5


/*connected to port N*/
#define LED1_PIN	1
#define LED1_PORT GPIO_PORT_N

#define LED2_PIN	0
#define LED2_PORT GPIO_PORT_N

/*connected to port F*/
#define LED3_PIN	4
#define LED3_PORT GPIO_PORT_F

#define LED4_PIN	0
#define LED4_PORT GPIO_PORT_F


void INIT_LED_1(void);
void INIT_LED_2(void);

void INIT_LED_3(void);
void INIT_LED_4(void);

void LED_TURN_ON(uint8_t portBase, uint8_t pinNO);
void LED_TURN_OFF(uint8_t portBase, uint8_t pinNO);
void LED_TOGGLE_STATE(uint8_t portBase, uint8_t pinNO);

#endif
