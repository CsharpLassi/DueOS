#include "debug.h"
#include "console.h"
#include "pmm.h"
#include "string.h"
#include "task.h"

void PrintTasks(void)
{
  TaskState* ft = GetFirstTask();
  while (ft != 0)
  {
    PrintString("Task %x\n",ft);
    PrintString("-Addr %x\n",ft);
    PrintString("-State %x\n",ft->state);
    PrintString("-Stack %x\n",ft->stack);

    ft = ft->nexttask;
  }
}

void PrintMalloc(void)
{
  MemorySegment* ms = PmmGetFirstMemorySegment();
  while (ms != 0)
  {
    PrintString("Segment %x\n",ms);
    PrintString("-Taskhandle %x\n",ms->taskhandle);
    PrintString("-Length %x\n",ms->length);

    ms = ms->nextsegment;
  }
}

void PrintIrq(void)
{
}

void DebugLoop(void)
{
  PrintString("Debugmodus aktiviert\n");

  char* str = (char*)PmmMalloc(64);

  while(!ReadLine(str,64) && !StringCompare(str,"end") )
  {
    if(StringCompare(str,"gettasks")) PrintTasks();
    else if(StringCompare(str,"getmalloc")) PrintMalloc();
    else if(StringCompare(str,"getirq")) PrintIrq();
  }

  PrintString("Debugmodus deaktiviert\n");
  PmmFree((uint8_t*)str);
}
