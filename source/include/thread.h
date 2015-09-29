#ifndef __THREAD_H__
#define __THREAD_H__

#include "irqstate.h"
#include "stdint.h"


void InitThread();
void AddThread(void* entry,uint8_t* stack);

irqstate* NextThread(irqstate* oldthread);


#endif
