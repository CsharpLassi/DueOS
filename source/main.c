#include "sam3x8e.h"
#include "console.h"
#include "uart.h"

int main(void)
{
	SystemInit();

	//Uart aktivieren
	configure_uart();

	//Fehler aktivieren
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk;

	//Watchdog
	WDT->WDT_MR |=WDT_MR_WDDIS;


	SysTick_Config(0xFFFFFF);

	//Erlaube Int.
	__enable_irq();

	//uprintf("Hallo Welt!");

	//Kernel Thread
	while (1)
	{
	}
}
