#ifndef __MEMORYSEGMENT_H__
#define __MEMORYSEGMENT_H__

#include <stdint.h>

struct MemorySegment
{
  uint32_t length;
  uint32_t taskhandle;
  struct MemorySegment* nextsegment;
}__attribute__((packed));
typedef struct MemorySegment MemorySegment;


#endif
