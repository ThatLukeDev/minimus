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
		pusha
		call idt%1
		popa
		iret
%endmacro

idt 32
idt 33
idt 35
idt 36
idt 37
idt 38
idt 39
idt 40
idt 41
idt 42
idt 43
idt 44
idt 45
idt 46
idt 47

idt 70
idt 71
idt 72
idt 73
