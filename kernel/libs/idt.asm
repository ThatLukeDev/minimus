global initidtasm
global interrupthandler
global idtdescriptor

section .data

idtdescriptor:
	dd 0x10000	; address
	dw 256*8-1	; size

section .text

initidtasm:
	lidt [idtdescriptor]
	ret


extern _idtfunc0
global _idthandler0
_idthandler0:
	call _idtfunc0
	iret
