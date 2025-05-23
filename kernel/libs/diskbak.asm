extern realmode
extern procmode
extern moderetaddr

global diskbak

section .text

diskbak:
xchg bx, bx
	mov [moderetaddr], WORD reel
	jmp realmode
[bits 16]
reel:
	int 0x13 ; test

	mov [moderetaddr], WORD deel
	jmp procmode
[bits 32]
deel:
	ret
