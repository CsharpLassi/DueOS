#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#include <stdint.h>

void  CloseTask(void);

uint8_t* Malloc( uint32_t length);

#endif
