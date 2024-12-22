#include "pic.h"
#include "ioutils.h"
#include "keyboard.h" //this

#include "console.h"

char scancodetoascii[256] = {
	0x0,	0x0,	'1',	'2',	'3',	'4',	'5',	'6',
	'7',	'8',	'9',	'0',	'-',	'=',	0x0,	0x0,
	'q',	'w',	'e',	'r',	't',	'y',	'u',	'i',
	'o',	'p',	'[',	']',	0X0,	0X0,	'a',	's',
	'd',	'f',	'g',	'h',	'j',	'k',	'l',	';',
	'\'',	'`',	0X0,	'#',	'z',	'x',	'c',	'v',
	'b',	'n',	'm',	',',	'.',	'/',	0X0,	0X0,
	0x0,	' ',	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

unsigned char keyStates[128];

void (*keyboardHooks[256])(char);

void keyStateChanged() {
	unsigned char scancode = inb(0x60);
	unsigned char scankeycode = scancode & 0b01111111;
	unsigned char pressed = scancode >> 7;

	keyStates[scankeycode] = pressed;

	for (int i = 0; i < 256; i++) {
		if (keyboardHooks[i]) {
			keyboardHooks[i](scancode);
		}
	}
}

int addKeyboardHook(void (*func)(char)) {
	for (int i = 0; i < 256; i++) {
		if (!keyboardHooks[i]) {
			keyboardHooks[i] = func;
			return 0;
		}
	}
	return -1;
}

void removeKeyboardHook(void (*func)(char)) {
	int offset = 0;

	for (int i = 0; i < 256 - offset; i++) {
		if (keyboardHooks[i] == func) {
			offset = 1;
		}
		keyboardHooks[i] = keyboardHooks[i + offset];
	}
}

void initkeyboard() {
	for (int i = 0; i < 256; i++)
		keyboardHooks[i] = 0;
	addPicFunc(1, keyStateChanged);
	for (int i = 0; i < 64; i++) {
		keyStates[i] = 1;
	}
}
