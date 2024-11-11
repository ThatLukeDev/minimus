global getvgafont

getvgafont:
pusha
	mov eax, 4
	mov [0x0a0000], eax
popa
ret

	pusha

	; clear even/odd mode
	mov dx, 0x03ce
	mov ax, 5
	out dx, ax

	;map vga memory to 0x0a0000
	mov ax, 0x0406
	out dx, ax

	;set bitplane 2
	mov dx, 0x03c4
	mov ax, 0x0402
	out dx, ax

	;clear even/odd mode (doesnt follow spec)
	mov ax, 0x0604
	out dx, ax

	; copy charmap
	mov esi, 0x0a0000
	mov ecx, 256

moveloop:
	; copy 16 bytes
	movsd
	movsd
	movsd
	movsd

	; skip last 16 bytes
	add esi, 16
	loop moveloop

	; set normal vga
	mov ax, 0x0302
	out dx, ax
	mov ax, 0x0204
	out dx, ax
	mov dx, 0x03ce
	mov ax, 0x1005
	out dx, ax
	mov ax, 0x0e06
	out dx, ax

	popa
	ret
