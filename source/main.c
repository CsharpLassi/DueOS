#include "sam3x8e.h"
#include "uart.h"
#include "console.h"


int main(void)
{
	// Initialize the SAM system
	SystemInit();

	configure_uart();

	while (1)
	{
		uprintf("Hallo Welt %x \n",10);
	}
}
