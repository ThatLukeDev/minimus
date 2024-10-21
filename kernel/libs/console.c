#define VMEM_START (char*)0xb8000
#define VMEM_END (char*)0xbfd00
#define LINE_WIDTH 160
#include <stdarg.h>
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
		}
		else {
			putc(*s);
		}
		s++;
	}
}

void printf(char* str, ...) {
	va_list ap;

	va_start(ap, str);
	while (*str != 0) {
		if (*str == '\n') {
			cursor = (char*)((cursor - VMEM_START) / LINE_WIDTH * LINE_WIDTH + LINE_WIDTH + VMEM_START);
		}
		else if(*str == '%') {
			str++;
			if (*str == '%') {
				putc(*str);
			}
			else if (*str == 's') {
				puts(va_arg(ap, char*));
			}
			else if (*str == 'd') {
				int val = va_arg(ap, int);
				if (val < 0) {
					putc('-');
					val *= -1;
				}
				char buf[100];
				int i = 0;
				if (val == 0) {
					buf[i++] = (char)(val % 10 + 48);
				}
				while (val > 0) {
					buf[i++] = (char)(val % 10 + 48);
					val /= 10;
				}
				for (i--; i >= 0; i--)
					putc(buf[i]);
			}
		}
		else {
			putc(*str);
		}
		str++;
	}
	va_end(ap);
}
