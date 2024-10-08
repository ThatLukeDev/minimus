[bits 16]			; Real mode
[org 0x7c00]			; MBR location

KERNEL_OFFSET equ 0x1000	; kernal load location

; stack pointers
mov sp, 0x9000		; top of stack
mov bp, 0x9000		; bottom of stack

; read kernel
mov bx, KERNEL_OFFSET	; destination
; mov dl, [DISK]	; disk already in dl
mov ah, 0x02		; set read mode
mov cl, 0x02		; start from sec 2 (sec 1 is boot, sec 2 is kernel)
mov al, 2		; num sectors
mov ch, 0x00		; cylinder
mov dh, 0x00		; head
int 0x13		; call
jc $			; carry bit stores error, loop
cmp al, dh		; al is sectors read
jne $			; if al isnt sectors read, loop

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
	db 0b10011010	; flags (see wiki)
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
	call KERNEL_OFFSET	; hand control to kernel
	jmp $			; return -> error, loop

; padding
times 510 - ($-$$) db 0

; boot signature
dw 0xaa55
