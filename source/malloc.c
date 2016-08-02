#include<stdint.h>

#include "malloc.h"

uint8_t segments[SEGMENTCOUNT];

uint8_t* malloc(uint32_t length)
{
  uint16_t segmentcount = length / (SEGMENTSIZE);
  if (length % SEGMENTSIZE)
    segmentcount++;

  uint8_t* startsegement = 0;

  for (uint32_t i = 0; i < SEGMENTCOUNT * 8 && segmentcount > 0; i++)
  {
    if (!(segments[i>>3] & (1<<(i%8))))
    {
      if(startsegement == 0)
        startsegement = PAGESTART + i * 64;

      segmentcount--;
      segments[i>>3] |= 1 << (i % 8);
    }
  }

  return startsegement;
}
