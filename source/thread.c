#include "thread.h"
#include "console.h"
#include "irqstate.h"

#define STACKSIZE 4096

uint8_t stack_a[STACKSIZE];
uint8_t stack_b[STACKSIZE];

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
  AddThread(&TaskA,&stack_a[0]);
  AddThread(&TaskB,&stack_b[0]);
}
void AddThread(void* entry,uint8_t* stack)
{
  irqstate* state = (irqstate*)(stack + STACKSIZE) -1;
  state->sp = (uint32_t) ((stack + STACKSIZE));
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
