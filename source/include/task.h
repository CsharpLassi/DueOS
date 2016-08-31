#ifndef __TASK_H__
#define __TASK_H__

#include <stdint.h>
#include "irqstate.h"
#include "taskstate.h"

taskstate* getfirsttask();

void inittask(void);
void registertask(void* entrypoint);
void exittask(void);

uint32_t getcurrenttaskhandle();

irqstate* closecurrenttask(void);
irqstate* nexttask(irqstate* oldstate);

#endif
