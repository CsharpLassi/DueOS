#include <stdint.h>

#include "irqstate.h"
#include "task.h"
#include "taskstate.h"
#include "console.h"
#include "malloc.h"

#include "sam3x8e.h"

#define TASKCOUNT 8

taskstate states[TASKCOUNT];

taskstate* currenttask;
uint8_t currenttasknumber = 0;

void registertask(void* entrypoint)
{
    //TODO: Böse
    __disable_irq();

  for (uint8_t i = 1; i < TASKCOUNT; i++) {
      if (!states[i].enable) {

        states[i].enable = 1;
        uint8_t* stack = (irqstate*)malloc(256);

        states[i].state =(irqstate*)(stack+256-sizeof(irqstate));
        states[i].state->psr = 0x41000000;
        states[i].state->pc = (uint32_t)entrypoint-1;
        states[i].state->sp = (stack+256);
        break;
      }
  }
  __enable_irq();
}

irqstate* nexttask(irqstate* oldtask)
{

  states[currenttasknumber].state = oldtask;
  if (currenttasknumber == 0)
    states[0].enable = 1;

  uint8_t nexttasknumber= currenttasknumber;


  do {
    nexttasknumber = (nexttasknumber +1)%TASKCOUNT;
  } while(!states[nexttasknumber].enable);

  currenttasknumber = nexttasknumber;
  currenttask = &states[currenttasknumber];

  //uprintf("%d\n",currenttasknumber);

  return currenttask->state;
}
