#include "sam3x8e.h"
#include "console.h"
#include "uart.h"
#include "malloc.h"

#include <stdio.h>
#include "syscalls.h"ma

#include "task.h"

volatile uint8_t* stack;

void testtask1() {
	while(1)
	{
		uprintf("Hallo TestTask 1\n");
	}
}

void testtask2() {
	while(1)
	{
		uprintf("Hallo TestTask 2\n");
		exit();
	}
}

int main(void)
{
	SystemInit();

	//Uart aktivieren
	configure_uart();

	//KernelMalloc
	stack = malloc(4096);

	//TaskInit
	inittask();

	//Fehler aktivieren
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk;

	//Watchdog
	WDT->WDT_MR |=WDT_MR_WDDIS;


	SysTick_Config(0xFFFFFF);

	registertask(&testtask1);
	registertask(&testtask2);

	//Erlaube Int.
	__enable_irq();

	//Kernel Thread
	while (1)
	{
		uprintf("Hallo Welt!\n");
	}
}
