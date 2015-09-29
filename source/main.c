#include "sam3x8e.h"
#include "uart.h"
#include "console.h"
#include "thread.h"
#include "pmm.h"



int main(void)
{
	// Initialize the SAM system
	SystemInit();
	configure_uart();
	pmm_init();

	InitThread();

	uprintf("Faultsenable\n");
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk  | SCB_SHCSR_BUSFAULTENA_Msk  | SCB_SHCSR_MEMFAULTENA_Msk ;

	uprintf("Watchdog State: %d\n",WDT->WDT_MR & WDT_MR_WDDIS);
	uprintf("Watchdog off\n");
	WDT->WDT_MR |= WDT_MR_WDDIS;

	uprintf("Config Systick\n");
	SysTick_Config(0xFFFFFF);

	uprintf("Eanble IRQ\n");
	__enable_irq();



	//Kernel Thread
	while (1)
	{
	}
}
