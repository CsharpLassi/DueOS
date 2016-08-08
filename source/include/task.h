#ifndef __TASK_H__
#define __TASK_H__

#include <stdint.h>
#include "irqstate.h"

void inittask(void);
void registertask(void* entrypoint);

void exittask(void);

irqstate* closecurrenttask(void);
irqstate* nexttask(irqstate* oldstate);

#endif
