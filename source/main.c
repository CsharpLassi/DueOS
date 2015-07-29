#include "sam3x8e.h"
#include "uart.h"
#include "stdio.h"


int main(void)
{
	// Initialize the SAM system
	SystemInit();

	configure_uart();

	while (1)
	{
		printf("Hallo Welt\n");
	}
}
