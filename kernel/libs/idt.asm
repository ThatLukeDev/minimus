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

%macro idt 1
	extern idt%1
	global _idt%1
	_idt%1:
		call idt%1
		iret
%endmacro

idt 33
