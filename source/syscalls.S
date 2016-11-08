.syntax unified
.thumb

.global exit
.global malloc
.global malloc_irq

.extern pmm_malloc

.text

exit:
  svc 0x00
  bx lr

malloc:
  svc 0x01
  bx lr

malloc_irq:
  b pmm_malloc
