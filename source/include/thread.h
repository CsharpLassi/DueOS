#ifndef __THREAD_H__
#define __THREAD_H__

#include "irqstate.h"
#include "stdint.h"

struct threadstate
{
  irqstate* state;
  uint8_t* stack;
  struct threadstate* nextthread;
};
typedef struct threadstate threadstate;


void InitThread();
threadstate* AddThread(void* entry);
void FreeThread(threadstate* thread);
irqstate* NextThread(irqstate* oldthread);


#endif
