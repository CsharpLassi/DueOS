#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdarg.h>
#include <stdint.h>

int GetChar(char* c);
int PutChar(const char c );
int PutString(const char* str);
int PutInteger(uint32_t value,uint8_t base);
int PrintString(const char* str, ...);
int ReadLine(char* str,uint8_t size);

#endif
