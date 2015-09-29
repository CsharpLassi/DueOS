#include "thread.h"
#include "console.h"
#include "irqstate.h"
#include "pmm.h"

irqstate* states[3];
uint8_t threadcount = 0;
uint8_t currentstate = 0;


void TaskA()
{
  while (1)
  {
    uprintf("TaskA\n");
  }
}

void TaskB()
{
  while (1)
  {
    uprintf("TaskB\n");
  }
}

void InitThread()
{
  threadcount++;
  currentstate = 1;
  AddThread(&TaskA);
  AddThread(&TaskB);
}
void AddThread(void* entry)
{
  uint8_t* stack = pmm_alloc();

  irqstate* state = (irqstate*)(stack + 1024) -1;
  state->sp = (uint32_t) ((stack + 1024));
  state->psr = 0x41000000;
  state->pc = (uint32_t) entry - 1;



  states[threadcount] = state;
  threadcount++;
}

irqstate* NextThread(irqstate* oldthread)
{
  if (currentstate == 0 )
    states[ threadcount -1] = oldthread;
  else
    states[ currentstate -1] = oldthread;

  irqstate* state = states[currentstate];

  currentstate++;
  currentstate %= threadcount;

  return state;
}
