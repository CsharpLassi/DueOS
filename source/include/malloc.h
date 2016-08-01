#ifndef __MALLOC_H__
#define __MALLOC_H__

#include <stdint.h>

#define PAGESTART 0x20000000
#define PAGELENGTH 0x00018000
#define SEGMENTSIZE 64
#define SEGMENTCOUNT PAGELENGTH/(SEGMENTSIZE *8)

uint8_t* malloc(uint32_t length);

#endif
