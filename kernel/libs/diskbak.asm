extern realmode
extern procmode
extern moderetaddr

global diskbak

section .text

pak_size:
db 16
pak_null:
db 0
pak_sect:
dw 1
bak_buffer:
dd 0
bak_lba_lower:
dd 0
bak_lba_upper:
dd 0
bak_rwx:
db 0
diskbak:
	mov [moderetaddr], WORD reel
	jmp realmode
[bits 16]
reel:
	; extended mode lba bios func int 0x13
	mov si, pak_size
	mov ah, 0x42
	or ah, [bak_rwx]
	mov dl, 0x80
	int 0x13

	mov [moderetaddr], WORD deel
	jmp procmode
[bits 32]
deel:
	ret
