[org 0x7c00]		; memory load location
[bits 16]		; real mode

KERNEL_SEGS equ 64	; KERNEL_SEGS is in segments, where each segment is 512 bytes

; read kernel (https://en.wikipedia.org/wiki/INT_13H)
mov bx, 0
mov es, bx
mov bx, 0x7e00		; offset
mov ah, 0x02		; set read mode
mov cl, 2		; start from sec 2 (sec 1 is boot, sec 2 is kernel)
mov al, KERNEL_SEGS	; sectors to read
mov ch, 0		; cylinder
mov dh, 0		; head
int 0x13		; call
jc $$			; carry bit stores error, loop
cmp al, KERNEL_SEGS	; al is sectors read
jne $$			; if all sectors arent read, loop

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

; get largest availible memory block
pusha			; push all
mov cx, 0x0		; clear cx for addition later
xor eax, eax
mov es, eax
mov ebx, 0x0		; clear
mov edx, 0x534d4150	; magic value
memreadloop:
	mov eax, 0xe820		; magic value
	mov ecx, 0x18		; magic value
	mov di, 0x7bd0		; memory location for buffer
	int 0x15		; call function
	add di, cx		; increment di by entry size (cx is 16 bit cl)
memreadloopvalid:
	mov eax, [0x7be0]	; load type
	cmp eax, 1		; check if 1 (availible memory)
	jne memreadloopend	; go to next otherwise
memreadloopcheck:
	mov eax, [0x7bda]	; load size of current
	mov ecx, [0x7bfa]	; load size of biggest
	cmp eax, ecx		; check if bigger
	jle memreadloopend	; go to next otherwise
memreadlooprecord:
	mov eax, [0x7bd0]	; load address of current
	mov [0x7bf0], eax	; record biggest address
	mov eax, [0x7bd4]	; load address of current
	mov [0x7bf4], eax	; record biggest address
	mov eax, [0x7bd8]	; load size of current
	mov [0x7bf8], eax	; record biggest size
	mov eax, [0x7bdc]	; load size of current
	mov [0x7bfc], eax	; record biggest size
memreadloopend:
	cmp ebx, 0		; check if next
	jnz memreadloop		; repeat

; vga mode
mov ah, 0x0		; graphics mode
mov al, 0x13		; 256 colour 200x320
int 0x10		; set vga mode

; get vga font
mov eax, 0x100
mov es, eax
mov ax, 0x0
mov di, ax
push ds
push es
mov ax, 0x1130		; magic numbers
mov bh, 0x6
int 0x10		; get vga font
;mov ds, es
push es
pop ds
pop es
mov si, bp
mov cx, 0x400
rep movsd
pop ds

popa			; pop all

cli			; disable interrupts
lgdt [gdt_end]		; gdt_end is descritor table descriptor
mov eax, cr0
or eax, 1		; set 1 bit in control register for protected mode
mov cr0, eax
jmp (gdt_code - gdt_start):bits32code	; stall cpu and flush all cache (as moving to different segment) to finalize protected mode

; finally 32 bits
[bits 32]
bits32code:

xor al, al
call a20wait		; wait for write
mov al, 0xad
out 0x64, al		; send 0xad
call a20wait		; wait for write
mov al, 0xd0
out 0x64, al		; send 0xd0
call a20waitr		; wait for read
in al, 0x60		; get ack
push eax
call a20wait		; wait for write
mov al, 0xd1
out 0x64, al		; send 0xd1
call a20wait		; wait for write
pop eax			; eax gets overwritten
or al, 0b0010		; a20 bit
out 0x60, al		; set a20 bit on
call a20wait		; wait for write
mov al, 0xae
out 0x64, al		; send 0xae
call a20wait		; wait for generic
jmp skipa20		; go to end
a20wait:
	in al,0x64
	test al,2
	jnz a20wait
	ret
a20waitr:
	in al,0x64
	test al,1
	jz a20waitr
	ret

skipa20:
; stall cpu and flush all cache (as moving to different segment) to keep protected mode
jmp (gdt_code - gdt_start):start_kernel

start_kernel:
	; segment registers init
	mov ax, gdt_data - gdt_start
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; stack pointers
	mov esp, 0x7000		; top of stack
	mov ebp, esp		; bottom of stack

	call kernel		; start kernel and move back to segment

; kernel
kernel:
	jmp kernel_loadseg	; hand control to kernel
	jmp $$			; return -> error, loop

; padding
times 510 - ($-$$) db 0

; boot signature
db 0x55,0xaa

; kernel load
kernel_loadseg:
call kernel_cseg
jmp $				; if fail restart
kernel_cseg:			; compiled c appeneded here
