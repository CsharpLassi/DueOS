#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdarg.h>

#include "sam3x8e.h"

int ugetc(char *c);
int uputc(const char c);
int uputs(const char* str);
int uputn(uint32_t value,uint8_t base);
int uprintf(const char* str, ...);

#endif __STDIO_H__
