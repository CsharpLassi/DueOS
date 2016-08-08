#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdarg.h>
#include <stdint.h>

int ugetc(char* c);
int uputc(const char c );
int uputs(const char* str);
int uputn(uint32_t value,uint8_t base);
int uprintf(const char* str, ...);
int ureadln(char* str,uint8_t size);

#endif
