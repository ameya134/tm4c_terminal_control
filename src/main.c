
#include <main.h>

#include "bsp.h"
#include "systick.h"

#include "app.h"


void delayloop(uint8_t delay){

	uint16_t i;

	for(;delay>0;delay--){
		for(i=0;i<1000;i++);
	}

}


int main(void){


	appTaskInit();


	SysTickIntEnable(SYSTICK_PERIOD_ms);

	while(1){
		// wait for interrupt in low power sleep mode
		__asm("wfi");
	}


	return 0;
}
