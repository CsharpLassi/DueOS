#ifndef __PMM_H__
#define __PMM_H__

#include "stdint.h"

void pmm_init();
uint8_t* pmm_alloc();
void pmm_free(uint8_t* page);

#endif
