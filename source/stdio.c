#include "sam3x8e.h"
#include "stdio.h"


int getc(uint8_t *c)
{
	// Check if the receiver is ready
	if((UART->UART_SR & UART_SR_RXRDY) == 0)
	return 1;

	// Read the character
	*c = (uint8_t) UART->UART_RHR;
	return 0;
}

int putc(const uint8_t c)
{
	// Check if the transmitter is ready
	while(!(UART->UART_SR & UART_SR_TXRDY))
	{
		
	}

	// Send the character
	UART->UART_THR = c;
	return 0;
}

int printf(const uint8_t* str)
{
	for (uint32_t i = 0;  str[i] != '\0'; i++)
	{
		if (putc(str[i]))
			return 1;
	}

	return 0;
}
