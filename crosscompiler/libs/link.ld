SECTIONS {
	.text 0x7e07 : { *(.text*) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	.bss : { *(.bss) }
	.got.plt : { *(.got.plt) }
	/DISCARD/ : { *(*) }
}
