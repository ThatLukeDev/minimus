[bits 16]			; Real mode
[org 0x7c00]			; MBR location

KERNEL_OFFSET equ 0x1000	; kernal load location

; stack pointers
mov sp, 0x9000	; top of stack
mov bp, 0x9000	; bottom of stack

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
	; marker
