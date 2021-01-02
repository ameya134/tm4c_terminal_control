
#include <main.h>

#include "bsp.h"
#include "systick.h"

#include "app.h"
#include "terminal.h"


int main(void){


	appTaskInit();


	SysTickIntEnable(SYSTICK_PERIOD_ms);

	while(1){
		// wait for interrupt in low power sleep mode
		__asm("wfi");
		terminalBackgroundTask();
	}


	return 0;
}
