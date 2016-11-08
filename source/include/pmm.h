#ifndef __MALLOC_H__
#define __MALLOC_H__

#include <stdint.h>
#include "memorysegment.h"

#define KERNELSTACK 4096
#define PAGESTART 0x20000000 + KERNELSTACK
#define PAGELENGTH 0x00018000 - KERNELSTACK

uint8_t* pmm_malloc(uint32_t length);
void pmm_free(uint8_t* addr);

memorysegment* pmm_getfirstmemorysegment();

#endif
