#include <stdint.h>
#include "sam3x8e.h"

#include "irqstate.h"
#include "task.h"
#include "taskstate.h"
#include "console.h"
#include "pmm.h"
#include "syscalls.h"


TaskState* _firsttask;
TaskState* _currenttask;

TaskState*  GetFirstTask()
{
  return _firsttask;
}

void InitTask(void)
{
  _firsttask = (TaskState*)PmmMalloc(sizeof(TaskState));
  _firsttask->nexttask = 0;
  _currenttask = _firsttask;
}

void RegisterTask(void* entrypoint)
{
    TaskState* task = (TaskState*)PmmMalloc(sizeof(TaskState));
    uint8_t* stack = PmmMalloc(256);

    task->state =(IrqState*)(stack+256-sizeof(IrqState));
    task->state->psr = 0x41000000;
    task->state->pc = (uint32_t)entrypoint-1;
    task->state->sp = (uint32_t)(stack+256);
    task->state->lr = (uint32_t)&ExitTask;
    task->nexttask =  (uint32_t)0;
    task->stack = stack;

    TaskState* lasttask = _firsttask;
    while (lasttask->nexttask != 0)
      lasttask = lasttask->nexttask;

   lasttask->nexttask = task;
}

void ExitTask(void)
{
  CloseTask();
}

IrqState* CloseCurrentTask(void)
{

  if (_currenttask == _firsttask)
    return _currenttask->state;

  TaskState* lasttask = _firsttask;
  while (lasttask->nexttask != _currenttask)
    lasttask = lasttask->nexttask;

  if(_currenttask->nexttask != 0)
    lasttask->nexttask = _currenttask->nexttask;
  else
    lasttask->nexttask = _firsttask;

  PmmClean((uint32_t)_currenttask);
  PmmFree((uint8_t*)_currenttask->stack);
  PmmFree((uint8_t*)_currenttask);

  _currenttask = lasttask->nexttask;


  return _currenttask->state;
}

IrqState* NextTask(IrqState* oldstate)
{
  _currenttask->state = oldstate;

  if (_currenttask->nexttask != 0)
    _currenttask = _currenttask->nexttask;
  else
    _currenttask = _firsttask;

  return _currenttask->state;
}

uint32_t GetCurrentTaskHandle()
{
  return (uint32_t)_currenttask;
}
