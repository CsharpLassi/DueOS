#include <stdint.h>

#include "sam3x8e.h"
#include "console.h"
#include "uart.h"
#include "pmm.h"
#include "syscalls.h"
#include "task.h"
#include "debug.h"
#include "string.h"


void TestTask1() {
	PrintString("TestTask 1 Start");
	volatile uint8_t* ic = Malloc(16);
	while(1)
	{
		PrintString("TestTask 1");
		(*ic) = 1;
	}
}

int main(void)
{
	SystemInit();


	//Uart aktivieren
	ConfigureUart();

	//TaskInit
	InitTask();

	//Fehler aktivieren
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk;

	//Watchdog
	WDT->WDT_MR |=WDT_MR_WDDIS;



	SysTick_Config(0xFFFF);

	RegisterTask(&TestTask1);
	//registertask(&testtask2);

	//Erlaube Int.
	__enable_irq();

	char* ic = (char*)PmmMalloc(64);
	//Kernel Thread
	while (1)
	{
		ReadLine(ic,64);
		if(StringCompare(ic,"debug"))
			DebugLoop();

	}
}
