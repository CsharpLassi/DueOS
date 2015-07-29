#ifndef __STDIO_H__
#define __STDIO_H__

#include "sam3x8e.h"

int getc(uint8_t *c);
int putc(const uint8_t c);
int printf(const uint8_t* str);

#endif __STDIO_H__
