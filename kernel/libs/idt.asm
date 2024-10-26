global initidtasm
global interrupthandler
global idtdescriptor
global idtaddr

section .data

idtdescriptor:
	dw 256*8-1	; size
idtaddr:
	dd 0x10000	; address

section .text

initidtasm:
	lidt [idtdescriptor]
	ret

extern dividezero
global _dividezero
_dividezero:
	call dividezero
	iret
