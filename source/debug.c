#include "debug.h"
#include "console.h"
#include "pmm.h"
#include "string.h"
#include "task.h"

void printtasks(void)
{
  taskstate* ft = getfirsttask();
  while (ft != 0)
  {
    uprintf("Task %x\n",ft);
    uprintf("-Addr %x\n",ft);
    uprintf("-State %x\n",ft->state);
    uprintf("-Stack %x\n",ft->stack);

    ft = ft->nexttask;
  }
}

void printmalloc(void)
{
  memorysegment* ms = pmm_getfirstmemorysegment();
  while (ms != 0)
  {
    uprintf("Segment %x\n",ms);
    uprintf("-Taskhandle %x\n",ms->taskhandle);
    uprintf("-Length %x\n",ms->length);

    ms = ms->nextsegment;
  }
}

void debugloop(void)
{
  uprintf("Debugmodus aktiviert\n");

  char* str = pmm_malloc(64);

  while(!ureadln(str,64) && !strcmp(str,"end") )
  {
    if(strcmp(str,"gettasks")) printtasks();
    else if(strcmp(str,"getmalloc")) printmalloc();
  }

  uprintf("Debugmodus deaktiviert\n");
  pmm_free((uint8_t*)str);
}
