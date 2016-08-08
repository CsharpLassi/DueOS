#include "console.h"
#include "sam3x8e.h"
#include "irqhandler.h"

//TODO: Unschön
int ugetc(char *c)
{
	aquireirq();

	// Check if the receiver is ready
	while((UART->UART_SR & UART_SR_RXRDY) == 0);

	// Read the character
	*c = (uint8_t) UART->UART_RHR;
	releaseirq();

	return 0;
}

int ureadln(char* str,uint8_t size)
{
	aquireirq();

	uint8_t i = 0;
	while (i < size -1 && !ugetc(&str[i]) && str[i] != '\n')
		i++;

	str[i] = 0;

	return 0;

	releaseirq();
}

int uputc(const char c)
{
	// Check if the transmitter is ready
	while(!(UART->UART_SR & UART_SR_TXRDY));

	// Send the character
	UART->UART_THR = c;
	return 0;
}

int uputs(const char* str)
{

	while (*str) {
		uputc(*str++);
	}

	return 0;
}

int uputn(uint32_t value,uint8_t base)
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

	uputs(p);

	return 0;
}

int uprintf(const char* str,...)
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
					uputn(n,2);
					break;
				case 's':
					s = va_arg(ap,char*);
					uputs(s);
					break;
				case 'd':
				case 'u':
					n = va_arg(ap,uint32_t);
					uputn(n,10);
					break;
				case 'x':
				case 'p':
					n = va_arg(ap,uint32_t);
					uputn(n,16);
					break;
				case '%':
					uputc('%');
					break;
				default:
					uputc('%');
					uputc(*str);
					break;
			}
		}
		else
		{
			uputc(*str);
		}

		str++;
	}

	va_end(ap);

	return 0;
}
