.syntax unified
.text
.thumb



.global CloseTask
.global Malloc

.type CloseTask, %function
.type Malloc, %function

.func CloseTask
CloseTask:
  svc 0x00
  bx lr
.endfunc

.func Malloc
Malloc:
  svc 0x01
  bx lr
.endfunc
