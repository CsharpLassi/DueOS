#ifndef __THREAD_H__
#define __THREAD_H__

#include "irqstate.h"
#include "stdint.h"


void InitThread();
void AddThread(void* entry);
irqstate* NextThread(irqstate* oldthread);

struct threadstate
{
  irqstate* state;
  uint8_t* stack;
  struct threadstate* nextthread;
};
typedef struct threadstate threadstate;

#endif
