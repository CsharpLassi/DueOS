#include<stdint.h>

#include "pmm.h"
#include "memorysegment.h"
#include "console.h"
#include "task.h"

MemorySegment* _firstsegment = 0;

uint8_t* PmmMalloc(uint32_t length)
{
  uint8_t* resultsegment = 0;

  length += (4 -length %4);

  if (_firstsegment == 0)
  {
    _firstsegment = (MemorySegment*)PAGESTART;
    _firstsegment->length = length;
    _firstsegment->nextsegment = 0;

    _firstsegment->taskhandle = GetCurrentTaskHandle();

    resultsegment = (uint8_t*)_firstsegment + sizeof(MemorySegment);
  }
  else
  {
    MemorySegment* lastsegment = _firstsegment;
    while (lastsegment->nextsegment != 0 && (uint32_t)(lastsegment->nextsegment) - (uint32_t)lastsegment - lastsegment->length - sizeof(MemorySegment) < length + sizeof(MemorySegment) )
    {
      lastsegment = lastsegment->nextsegment;
    }
    MemorySegment* newsegment =  (MemorySegment*)((uint8_t*)(lastsegment +1) + lastsegment->length);
    newsegment->length = length;
    newsegment->nextsegment = lastsegment->nextsegment;
    newsegment->taskhandle = GetCurrentTaskHandle();

    lastsegment->nextsegment = newsegment;

    resultsegment = (uint8_t*)newsegment + sizeof(MemorySegment);
  }



  return resultsegment;
}

void PmmFree(uint8_t* addr )
{
  uint8_t* segment = (addr - sizeof(MemorySegment));
  MemorySegment* lastsegment = _firstsegment;
  while((uint8_t*)lastsegment->nextsegment != segment)
    lastsegment = lastsegment->nextsegment;

  lastsegment->nextsegment = lastsegment->nextsegment->nextsegment;

}

MemorySegment* PmmGetFirstMemorySegment()
{
  return _firstsegment;
}

void PmmClean(uint32_t handle)
{
  MemorySegment* lastsegment = _firstsegment;
  while((uint8_t*)lastsegment->nextsegment != 0)
  {
    if (lastsegment->taskhandle == handle)
    {
      lastsegment->nextsegment = lastsegment->nextsegment->nextsegment;
    }

    lastsegment = lastsegment->nextsegment;
  }
}
