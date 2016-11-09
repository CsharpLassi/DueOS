#ifndef __MALLOC_H__
#define __MALLOC_H__

#include <stdint.h>
#include "memorysegment.h"

#define KERNELSTACK 4096
#define PAGESTART 0x20000000 + KERNELSTACK
#define PAGELENGTH 0x00018000 - KERNELSTACK

uint8_t* PmmMalloc(uint32_t length);
void PmmFree(uint8_t* addr);

void PmmClean(uint32_t handle);

MemorySegment* PmmGetFirstMemorySegment();

#endif
