#ifndef __TASK_H__
#define __TASK_H__

#include <stdint.h>
#include "irqstate.h"

void registertask(void* entrypoint);

irqstate* nexttask(irqstate* oldstate);

#endif
