#ifndef __TASKSTATE_H__
#define __TASKSTATE_H__

#include <stdint.h>
#include "irqstate.h"

struct TaskState
{
  IrqState* state;
  uint8_t* stack;
  struct TaskState * nexttask;
} __attribute__((packed));
typedef struct TaskState TaskState;

#endif
