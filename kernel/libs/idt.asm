global initidt
global interrupthandler
global idtdescriptor

section .data

idtdescriptor:
	dd 0x10000	; address
	dw 256*8-1	; size

section .text

initidt:
	lidt [idtdescriptor]
	ret

interrupthandler:
	call esp
	iret
