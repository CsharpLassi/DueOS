#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

inline void exit()
{
  asm("svc 0x00");
}

#endif
