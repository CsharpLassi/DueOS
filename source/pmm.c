#include<stdint.h>

#include "pmm.h"
#include "memorysegment.h"
#include "console.h"
#include "task.h"

memorysegment* firstsegment = 0;

uint8_t* pmm_malloc(uint32_t length)
{
  uint8_t* resultsegment = 0;

  length += (4 -length %4);

  if (firstsegment == 0)
  {
    firstsegment = (memorysegment*)PAGESTART;
    firstsegment->length = length;
    firstsegment->nextsegment = 0;

    firstsegment->taskhandle = getcurrenttaskhandle();

    resultsegment = (uint8_t*)firstsegment + sizeof(memorysegment);
  }
  else
  {
    memorysegment* lastsegment = firstsegment;
    while (lastsegment->nextsegment != 0 && (uint32_t)(lastsegment->nextsegment) - (uint32_t)lastsegment - lastsegment->length - sizeof(memorysegment) < length + sizeof(memorysegment) )
    {
      lastsegment = lastsegment->nextsegment;
    }
    memorysegment* newsegment =  (memorysegment*)((uint8_t*)(lastsegment +1) + lastsegment->length);
    newsegment->length = length;
    newsegment->nextsegment = lastsegment->nextsegment;
    newsegment->taskhandle = getcurrenttaskhandle();

    lastsegment->nextsegment = newsegment;

    resultsegment = (uint8_t*)newsegment + sizeof(memorysegment);
  }



  return resultsegment;
}

void pmm_free(uint8_t* addr )
{
  uint8_t* segment = (addr - sizeof(memorysegment));
  memorysegment* lastsegment = firstsegment;
  while((uint8_t*)lastsegment->nextsegment != segment)
    lastsegment = lastsegment->nextsegment;

  lastsegment->nextsegment = lastsegment->nextsegment->nextsegment;

}

memorysegment* pmm_getfirstmemorysegment()
{
  return firstsegment;
}
