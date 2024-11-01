#include "pic.h"
#include "ioutils.h"
#include "keyboard.h" //this

#include "console.h"

char scancodetoascii[256] = {
	0x0,	0x0,	'1',	'2',	'3',	'4',	'5',	'6',
	'7',	'8',	'9',	'0',	'-',	'=',	0x0,	0x0,
	'Q',	'W',	'E',	'R',	'T',	'Y',	'U',	'I',
	'O',	'P',	'[',	']',	0x0,	0x0,	'A',	'S',
	'D',	'F',	'G',	'H',	'J',	'K',	'L',	';',
	'\'',	'`',	0x0,	'#',	'Z',	'X',	'C',	'V',
	'B',	'N',	'M',	',',	'.',	'/',	0x0,	0x0,
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

unsigned char keyStates[64];

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

void initkeyboard() {
	addPicFunc(1, keyStateChanged);
	for (int i = 0; i < 64; i++) {
		keyStates[i] = 1;
	}
}
