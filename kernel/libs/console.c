#define VMEM_START (char*)0xb8000
#define VMEM_END (char*)0xbfd00
char* cursor;

void clrscr() {
	for (cursor = VMEM_START; cursor < VMEM_END; cursor++)
		*cursor = 0;
	cursor = VMEM_START;
}

void putc(char c) {
	*cursor++=c;
	*cursor++=0x07;
}

void puts(char* s) {
	putc(s[0]);
	/*
	while (*s != 0) {
		putc(*s++);
	}
	*/
}
