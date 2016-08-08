#include "debug.h"
#include "console.h"
#include "malloc.h"
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

void debugloop(void)
{
  uprintf("Debugmodus aktiviert\n");

  char* str = malloc(64);

  while(!ureadln(str,64) && !strcmp(str,"end") )
  {
    if(strcmp(str,"gettasks")) printtasks();
  }

  uprintf("Debugmodus deaktiviert\n");
  free((uint8_t*)str);
}
