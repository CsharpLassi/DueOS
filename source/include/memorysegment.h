#ifndef __MEMORYSEGMENT_H__
#define __MEMORYSEGMENT_H__

#include <stdint.h>

struct memorysegment
{
  uint32_t length;
  struct memorysegment* nextsegment;
}__attribute__((packed));
typedef struct memorysegment memorysegment;


#endif
