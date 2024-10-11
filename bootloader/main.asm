[org 0x7c00]			; memory load location
[bits 16]			; real mode

KERNEL_OFFSET equ 0x7e00	; kernal load location
START equ 0x7c00

; stack pointers
mov sp, 0x9000		; top of stack
mov bp, 0x9000		; bottom of stack

; read kernel (https://en.wikipedia.org/wiki/INT_13H)
cld			; clear args
mov bx, KERNEL_OFFSET	; offset
mov ah, 0x02		; set read mode
mov cl, 2		; start from sec 2 (sec 1 is boot, sec 2 is kernel)
mov al, 2		; sectors to read
mov ch, 0		; cylinder
mov dh, 0		; head
int 0x13		; call
jc START		; carry bit stores error, loop
cmp al, 2		; al is sectors read
jne START		; if all sectors arent read, loop

jmp gdt_after

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
	db 0b11001111	; 4b flags (see wiki) + seg limit
	db 0		; segment base
gdt_end:
	dw gdt_end - gdt_start - 1	; limit
	dd gdt_start			; addr (actually 24 bit, 8 ignored)
gdt_after:

cli			; disable interrupts
lgdt [gdt_end]		; gdt_end is descritor table
push eax		; eax is tmp
mov eax, cr0
or eax, 1		; set 1 bit in control register
mov cr0, eax		; enables protected mode
pop eax
times 2 popa

; stall cpu and flush all cache (as moving to different segment)
jmp (gdt_code - gdt_start):start_kernel

; finally 32 bits
[bits 32]
start_kernel:
	; segment registers init
	mov ax, gdt_data - gdt_start
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; stack pointers
	mov esp, 0x9000		; top of stack
	mov ebp, 0x9000		; bottom of stack

	call kernel		; start kernel and move back to segment

; kernel
kernel:
	jmp KERNEL_OFFSET	; hand control to kernel
	jmp START		; return -> error, loop

; padding
times 510 - ($-$$) db 0

; boot signature
db 0x55,0xaa

; kernel load
call kernel_cseg
jmp $
kernel_cseg:
