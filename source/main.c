#include <stdint.h>

#include "irqhandler.h"
#include "sam3x8e.h"
#include "console.h"
#include "uart.h"
#include "pmm.h"
#include "syscalls.h"
#include "task.h"
#include "debug.h"
#include "string.h"

void testtask1() {
	while(1)
	{
	}
}

int main(void)
{
	SystemInit();

	//Uart aktivieren
	configure_uart();

	//TaskInit
	inittask();

	//Fehler aktivieren
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk;

	//Watchdog
	WDT->WDT_MR |=WDT_MR_WDDIS;


	SysTick_Config(0xFFFFFF);

	registertask(&testtask1);

	//Erlaube Int.
	releaseirq();

	char* ic = (char*)pmm_malloc(64);
	//Kernel Thread
	while (1)
	{

		ureadln(ic,64);
		if(strcmp(ic,"debug"))
			debugloop();

	}
}
