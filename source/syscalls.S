.syntax unified
.thumb

.global close
.global malloc

.text

close:
  svc 0x00
  bx lr

malloc:
  svc 0x01
  bx lr
