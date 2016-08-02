#include <stdint.h>

#include "irqstate.h"
#include "task.h"
#include "taskstate.h"
#include "console.h"
#include "malloc.h"

#include "sam3x8e.h"

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
    //TODO: Böse
    __disable_irq();

    taskstate* task = (taskstate*)malloc(sizeof(taskstate));
    uint8_t* stack = malloc(256);

    task->state =(irqstate*)(stack+256-sizeof(irqstate));
    task->state->psr = 0x41000000;
    task->state->pc = (uint32_t)entrypoint-1;
    task->state->sp = (stack+256);
    task->nexttask = 0;


    taskstate* lasttask = firsttask;
    while (lasttask->nexttask != 0)
      lasttask = lasttask->nexttask;

   lasttask->nexttask = task;

  __enable_irq();
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
