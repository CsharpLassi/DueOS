#include <stdint.h>
#include "sam3x8e.h"

#include "irqstate.h"
#include "task.h"
#include "taskstate.h"
#include "console.h"
#include "pmm.h"
#include "syscalls.h"


taskstate* firsttask;
taskstate* currenttask;

taskstate*  getfirsttask()
{
  return firsttask;
}

void inittask(void)
{
  firsttask = (taskstate*)pmm_malloc(sizeof(taskstate));
  firsttask->nexttask = 0;
  currenttask = firsttask;
}

void registertask(void* entrypoint)
{
    taskstate* task = (taskstate*)pmm_malloc(sizeof(taskstate));
    uint8_t* stack = pmm_malloc(256);

    task->state =(irqstate*)(stack+256-sizeof(irqstate));
    task->state->psr = 0x41000000;
    task->state->pc = (uint32_t)entrypoint-1;
    task->state->sp = (uint32_t)(stack+256);
    task->state->lr = (uint32_t)&exittask;
    task->nexttask =  (uint32_t)0;
    task->stack = stack;

    taskstate* lasttask = firsttask;
    while (lasttask->nexttask != 0)
      lasttask = lasttask->nexttask;

   lasttask->nexttask = task;
}

void exittask(void)
{
  close();
}

irqstate* closecurrenttask(void)
{

  if (currenttask == firsttask)
    return currenttask->state;

  taskstate* lasttask = firsttask;
  while (lasttask->nexttask != currenttask)
    lasttask = lasttask->nexttask;

  if(currenttask->nexttask != 0)
    lasttask->nexttask = currenttask->nexttask;
  else
    lasttask->nexttask = firsttask;

  pmm_clean((uint32_t)currenttask);
  pmm_free((uint8_t*)currenttask->stack);
  pmm_free((uint8_t*)currenttask);

  currenttask = lasttask->nexttask;


  return currenttask->state;
}

irqstate* nexttask(irqstate* oldstate)
{
  currenttask->state = oldstate;

  if (currenttask->nexttask != 0)
    currenttask = currenttask->nexttask;
  else
    currenttask = firsttask;

  return currenttask->state;
}

uint32_t getcurrenttaskhandle()
{
  return (uint32_t)currenttask;
}
