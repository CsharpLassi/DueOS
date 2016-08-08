#ifndef __MALLOC_H__
#define __MALLOC_H__

#include <stdint.h>
#include "memorysegment.h"

#define KERNELSTACK 4096
#define PAGESTART 0x20000000 + KERNELSTACK
#define PAGELENGTH 0x00018000 - KERNELSTACK

uint8_t* malloc(uint32_t length);
void free(uint8_t* addr);

memorysegment* getfirstmemorysegment();

#endif
