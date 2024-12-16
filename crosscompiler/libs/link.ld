ENTRY(main)

SECTIONS {
	.text : { *(.text.main) *(.text*) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	.bss : { *(.bss) }
	.got.plt : { *(.got.plt) }
	/DISCARD/ : { *(*) }
}
