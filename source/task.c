#include <stdint.h>
#include "sam3x8e.h"

#include "irqstate.h"
#include "task.h"
#include "taskstate.h"
#include "console.h"
#include "malloc.h"
#include "irqhandler.h"
#include "syscalls.h"


taskstate* firsttask;
taskstate* currenttask;



void inittask(void)
{
  firsttask = (taskstate*)malloc(sizeof(taskstate));
  firsttask->nexttask = 0;
  currenttask = firsttask;
}

void registertask(void* entrypoint)
{
    aquireirq();

    taskstate* task = (taskstate*)malloc(sizeof(taskstate));
    uint8_t* stack = malloc(256);

    task->state =(irqstate*)(stack+256-sizeof(irqstate));
    task->state->psr = 0x41000000;
    task->state->pc = (uint32_t)entrypoint-1;
    task->state->sp = (stack+256);
    task->state->lr = &exittask;
    task->nexttask = 0;
    task->stack = stack;

    taskstate* lasttask = firsttask;
    while (lasttask->nexttask != 0)
      lasttask = lasttask->nexttask;

   lasttask->nexttask = task;

   releaseirq();
}

void exittask(void)
{
  exit();
}

irqstate* closecurrenttask(void)
{
  aquireirq();

  if (currenttask == firsttask)
    return;

  taskstate* lasttask = firsttask;
  while (lasttask->nexttask != currenttask)
    lasttask = lasttask->nexttask;

  if(currenttask->nexttask != 0)
    lasttask->nexttask = currenttask->nexttask;
  else
    lasttask->nexttask = firsttask;

  free(lasttask->stack);
  free(lasttask);

  currenttask = lasttask->nexttask;

  releaseirq();

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
