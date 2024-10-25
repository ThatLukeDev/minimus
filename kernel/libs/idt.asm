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


extern _idtfunc0
global _idthandler0
_idthandler0:
	jmp 0x7c00	; tmp
	pusha
	call _idtfunc0
	popa
	add esp, 8
	iret
