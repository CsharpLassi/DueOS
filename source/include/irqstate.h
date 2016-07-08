#ifndef __IRQSTATE_H__
#define __IRQSTATE_H__

#include<stdint.h>

struct irqstate
{
  uint32_t r4;
  uint32_t r5;
  uint32_t r6;
  uint32_t r7;
  uint32_t r8;
  uint32_t r9;
  uint32_t r10;
  uint32_t r11;
  uint32_t response;
  uint32_t sp;
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t pc;
  uint32_t psr;
} __attribute__((packed));
typedef struct irqstate irqstate;

#endif //__IRQSTATE_H__
