#define VMEM_START (char*)0xb8000
#define VMEM_END (char*)0xbfd00
#define LINE_WIDTH 160
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
	while (*s != 0) {
		if (*s == '\n') {
			cursor = (char*)((cursor - VMEM_START) / LINE_WIDTH * LINE_WIDTH + LINE_WIDTH + VMEM_START);
			s++;
		}
		else
			putc(*s++);
	}
}
