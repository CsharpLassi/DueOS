#include "console.h"
#include "sam3x8e.h"

//TODO: Unschön
int GetChar(char *c)
{

	// Check if the receiver is ready
	while((UART->UART_SR & UART_SR_RXRDY) == 0);

	// Read the character
	*c = (uint8_t) UART->UART_RHR;

	return 0;
}

int ReadLine(char* str,uint8_t size)
{

	uint8_t i = 0;
	while (i < size -1 && GetChar(&str[i]) && str[i] != '\n')
		i++;

	str[i] = 0;

	return 0;

}

int PutChar(const char c)
{
	// Check if the transmitter is ready
	while(!(UART->UART_SR & UART_SR_TXRDY));

	// Send the character
	UART->UART_THR = c;
	return 0;
}

int PutString(const char* str)
{

	while (*str) {
		PutChar(*str++);
	}

	return 0;
}

int PutInteger(uint32_t value,uint8_t base)
{
	char buf[65];
	char* p;
	const char* code = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (base > 36) {
		return 1;
	}

	p = buf + 64;
	*p= '\0';

	do {
		*--p = code[value % base];
		value /= base;
	} while (value);

	PutString(p);

	return 0;
}

int PrintString(const char* str,...)
{
	va_list ap;
	const char*  s;
	uint32_t n;



	va_start(ap,str);

	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == '\0') {
				break;
			}

			switch (*str)
			{
				case 'b':
					n = va_arg(ap,uint32_t);
					PutInteger(n,2);
					break;
				case 's':
					s = va_arg(ap,char*);
					PutString(s);
					break;
				case 'd':
				case 'u':
					n = va_arg(ap,uint32_t);
					PutInteger(n,10);
					break;
				case 'x':
				case 'p':
					n = va_arg(ap,uint32_t);
					PutInteger(n,16);
					break;
				case '%':
					PutChar('%');
					break;
				default:
					PutChar('%');
					PutChar(*str);
					break;
			}
		}
		else
		{
			PutChar(*str);
		}

		str++;
	}

	va_end(ap);

	return 0;
}
