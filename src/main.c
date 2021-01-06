
#include <main.h>

#include "bsp.h"
#include "systick.h"

#include "app.h"
#include "terminal.h"


int main(void){


	/* Call the init task for application */
	appTaskInit();

	
	/* Enable the system timer to generate system ticks*/
	SysTickIntEnable(SYSTICK_PERIOD_ms);

	
	/* This is the background loop where background tasks
	 * are executed. when background tasks are completed
	 * system goes into a low power waiting for interrupt
	 * mode. */
	while(1){
	
		// wait for interrupt in low power sleep mode
		__asm("wfi");
		terminalBackgroundTask();
	}

	/* control should never reach here*/
	
	return 0;
}
