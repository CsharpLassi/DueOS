#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#include <stdint.h>

extern void close(void);

extern uint8_t* malloc( uint32_t length);

#endif
