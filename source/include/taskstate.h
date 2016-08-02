#ifndef __TASKSTATE_H__
#define __TASKSTATE_H__

#include <stdint.h>
#include "irqstate.h"

struct taskstate
{
  irqstate* state;
  uint8_t* stack;
  struct taskstate * nexttask;
} __attribute__((packed));
typedef struct taskstate taskstate;

#endif
