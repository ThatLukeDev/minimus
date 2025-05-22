global initidtasm
global interrupthandler
global idtdescriptor
global idtaddr
global inttest

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
idt 74
idt 75

idt 76
idt 77
idt 78

idt 79

idt 80
idt 81
idt 82

idt 83
idt 84

; segment descriptor (https://en.wikipedia.org/wiki/Segment_descriptor) (reverse order)
gdt_start:
	dq 0		; null byte start
gdt_code:
	dw 0xffff	; segment limit
	db 0,0,0	; segment base
	db 0b10011010	; flags (see wiki)
	db 0b11001111	; 4b flags (see wiki) + seg limit
	db 0		; segment base
gdt_data:
	dw 0xffff	; segment limit
	db 0,0,0	; segment base
	db 0b10010010	; flags (see wiki)
	db 0b10001111	; 4b flags (see wiki) + seg limit
	db 0		; segment base
gdt_end:
	dw gdt_end - gdt_start - 1	; limit
	dd gdt_start			; addr (actually 24 bit, 8 ignored)
stack1:
	dd 0
stack2:
	dd 0
real_idt:
	dw 0x3ff
	dd 0
inttest:
	pusha

	mov eax, esp
	mov [stack1], eax
	mov eax, ebp
	mov [stack2], eax

	xchg bx, bx

	cli

	lgdt [gdt_end]

	jmp 0x8:bits16

[bits 16]
bits16:
	; segment registers init
	mov ax, gdt_data - gdt_start
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov eax, cr0
	xor eax, 1 ; get rid of protected mode
	mov cr0, eax

	jmp 0x8:farjmp

farjmp:
	mov sp, 0x7050		; top of stack
	mov bp, sp		; bottom of stack

	mov ax, 0
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	lidt [real_idt]

	sti

[bits 32]
	xchg bx, bx
[bits 16]

	cli

	mov eax, cr0
	xor eax, 1 ; get back of protected mode
	mov cr0, eax

[bits 32]

	mov esp, [stack1]	; top of stack
	mov ebp, [stack2]	; bottom of stack

	popa

	call initidtasm

	sti

	ret
