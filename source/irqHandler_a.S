.syntax unified
.thumb_func

.extern HandleIrq
.global ASMHandleIrq

.text

ASMHandleIrq:
	mov r0, sp
	add r0, #32
	push {r0}

	push {r4-r11,lr}
	mov r4,lr
	mov r0,sp

	bl HandleIrq

	mov sp, r0
	mov lr, r4

	pop {r4-r11}
	pop {r1} // altes lr
	pop {r0}
	sub r0, #32
	mov sp,r0

	bx lr
