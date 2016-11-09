.syntax unified
.text
.thumb



.global close
.global malloc

.type close, %function
.type malloc, %function

.func close
close:
  svc 0x00
  bx lr
.endfunc

.func malloc
malloc:
  svc 0x01
  bx lr
.endfunc
