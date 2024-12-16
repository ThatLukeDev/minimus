#define VMEM_START (char*)0xb8000
#define VMEM_END (char*)0xb9000
#define LINE_WIDTH 160

#include <stdarg.h>

void putc(char c) {
	*(char*)0x1000 = c;
	__asm__ volatile ("int $71");
}

void puts(char* s) {
	*(unsigned int*)0x1000 = (unsigned int)s;
	__asm__ volatile ("int $71");
}

char getc() {
	__asm__ volatile ("int $72");
	return *(char*)0x1000;
}

char* gets() {
	__asm__ volatile ("int $73");
	return (char*)(*(unsigned int*)0x1000);
}

void clrscr() {
	__asm__ volatile ("int $74");
}

void showConsoleOutput(char val) {
	__asm__ volatile ("int $75");
	**(char**)0x1000 = val;
}

void printf(char* str, ...) {
	va_list ap;

	__asm__ volatile ("int $75");

	char** cursor = (char**)0x1000;
	char** _typecursor = (char**)0x1010;

	va_start(ap, str);
	while (*str != 0) {
		if (*str == '\n') {
			*cursor = (char*)((*cursor - VMEM_START) / LINE_WIDTH * LINE_WIDTH + LINE_WIDTH + VMEM_START);
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
			else if (*str == 'x') {
				unsigned int val = va_arg(ap, unsigned int);
				char buf[100];
				int i = 0;
				if (val == 0) {
					unsigned char vmod = val % 16;
					if (vmod < 10)
						buf[i++] = (char)(vmod + 48);
					else
						buf[i++] = (char)(vmod + 55);
				}
				while (val > 0) {
					unsigned char vmod = val % 16;
					if (vmod < 10)
						buf[i++] = (char)(vmod + 48);
					else
						buf[i++] = (char)(vmod + 55);
					val /= 16;
				}
				for (i--; i >= 0; i--)
					putc(buf[i]);
			}
			else if (*str == 'b') {
				unsigned int val = va_arg(ap, unsigned int);
				char buf[100];
				int i = 0;
				if (val == 0) {
					unsigned char vmod = val % 2;
					buf[i++] = (char)(vmod + 48);
				}
				while (val > 0) {
					unsigned char vmod = val % 2;
					buf[i++] = (char)(vmod + 48);
					val >>= 1;
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
	*_typecursor = *cursor;
	va_end(ap);
}
