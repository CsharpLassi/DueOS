.syntax unified
.thumb

.extern handle_irq
.global asm_handle_irq
.global asm_returntask

.text

asm_handle_irq:
	mov r0, sp
	add r0, #32
	push {r0}

	push {r4-r11,lr}
	mov r3,lr
	mov r0,sp

	bl handle_irq

	mov sp, r0
	mov lr, r3

	pop {r4-r11}
	pop {r1} // altes lr
	pop {r0}
	sub r0, #32
	mov sp,r0

	bx lr
