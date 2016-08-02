#ifndef __MALLOC_H__
#define __MALLOC_H__

#include <stdint.h>

#define PAGESTART 0x20000000
#define PAGELENGTH 0x00018000

uint8_t* malloc(uint32_t length);
void free(uint8_t* addr);

#endif
