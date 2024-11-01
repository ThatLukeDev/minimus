#include "keyboard.h"
#include "ioutils.h"
#include "memory.h"

#define VMEM_START (char*)0xb8000
#define VMEM_END (char*)0xb9000
#define LINE_WIDTH 160

#include <stdarg.h>

unsigned char showConsoleOutput = 1;

char* cursor;

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
	va_end(ap);
}

char _getcchar;
char _getnewline;

void consoleKeyboardHook(char scancode) {
	if (scancode & 0b10000000)
		return;

	if (scancode == SC_ENTER) {
		cursor = (char*)((cursor - VMEM_START) / LINE_WIDTH * LINE_WIDTH + LINE_WIDTH + VMEM_START);
		_getnewline = 1;
		return;
	}

	char asciicode = scancodetoascii[scancode];

	if (!asciicode)
		return;

	if (keyStates[SC_SHIFT])
		asciicode |= 0b00100000;

	if (showConsoleOutput)
		putc(asciicode);

	_getcchar = asciicode;
}

char getc() {
	_getcchar = 0;
	_getnewline = 0;
	while (!_getcchar && !_getnewline)
		iowait();
	return _getcchar;
}

char* gets() {
	unsigned int size = 1;
	char* str = malloc(size);

	_getnewline = 0;
	while (!_getnewline) {
		str = realloc(str, size++);
		str[size - 2] = getc();
	}

	return str;
}

void clrscr() {
	for (cursor = VMEM_START; cursor < VMEM_END; cursor++)
		*cursor = 0;
	cursor = VMEM_START;
	initkeyboard();
	addKeyboardHook(consoleKeyboardHook);
}
