#ifndef __TASK_H__
#define __TASK_H__

#include <stdint.h>
#include "irqstate.h"
#include "taskstate.h"

TaskState* GetFirstTask();

void InitTask(void);
void RegisterTask(void* entrypoint);
void ExitTask(void);

uint32_t GetCurrentTaskHandle();

IrqState* CloseCurrentTask(void);
IrqState* NextTask(IrqState* oldstate);

#endif
