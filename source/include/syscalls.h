#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#include <stdint.h>

extern void exit(void);

extern inline uint8_t* malloc( uint32_t length);

#endif
