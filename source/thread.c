#include "thread.h"
#include "console.h"
#include "irqstate.h"
#include "pmm.h"

uint8_t threadcount = 0;
uint8_t currentstate = 0;

uint16_t threadmap = 0x01;

threadstate* kernelstate;

void InitThread()
{
  kernelstate = (threadstate*)pmm_alloc();
  kernelstate->nextthread = 0x00;

  threadcount++;
  currentstate = 0;
}

threadstate* AllocThreadState()
{
  for (uint8_t i = 0; i < 16; i++) {
    if ((( 1 << i) & threadmap) == 0) {
      threadmap |= (1 << i);
      return kernelstate +i;
    }
  }

  return 0x00;
}

void FreeThreadState(threadstate* state)
{
  threadmap &= ~((1 << ((state - kernelstate)/ sizeof(threadstate) )));
}

threadstate* AddThread(void* entry)
{

  threadstate* cstate = kernelstate;
  while (cstate->nextthread != 0x00)
    cstate = cstate->nextthread;

  threadstate* newstate = AllocThreadState();
  cstate->nextthread = newstate;

  uint8_t* stack = pmm_alloc();
  newstate->stack = stack;

  irqstate* state = (irqstate*)(stack + 1024) -1;
  state->sp = (uint32_t) ((stack + 1024));
  state->psr = 0x41000000;
  state->pc = (uint32_t) entry - 1;


  newstate->nextthread = 0x00;
  newstate->state = state;
  threadcount++;

  return newstate;
}

void FreeThread(threadstate* thread)
{
  threadstate* fstate = kernelstate;
  while (fstate->nextthread != thread)
    fstate = fstate->nextthread;

  fstate->nextthread = thread->nextthread;

  FreeThreadState(thread);
}

irqstate* NextThread(irqstate* oldthread)
{
  threadstate* cstate = kernelstate;

  for (uint8_t i = 0;  i < currentstate; i++) {
    cstate = cstate->nextthread;
  }

  currentstate++;
  currentstate %= threadcount;

  cstate->state = oldthread;

  if (cstate->nextthread == 0x00)
    return kernelstate->state;
  else
    return cstate->nextthread->state;
}
