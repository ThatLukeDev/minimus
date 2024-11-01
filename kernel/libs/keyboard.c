#include "pic.h"
#include "ioutils.h"

#include "console.h"

char scancodetoascii[64] = {
	0x0,	0x0,	'1',	'2',	'3',	'4',	'5',	'6',
	'7',	'8',	'9',	'0',	'-',	'=',	0x0,	0x0,
	'Q',	'W',	'E',	'R',	'T',	'Y',	'U',	'I',
	'O',	'P',	'[',	']',	0x0,	0x0,	'A',	'S',
	'D',	'F',	'G',	'H',	'J',	'K',	'L',	';',
	'\'',	'`',	0x0,	'#',	'Z',	'X',	'C',	'V',
	'B',	'N',	'M',	',',	'.',	'/',	0x0,	0x0,
	0x0,	' ',	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
};

void keyStateChanged() {
	unsigned char scancode = inb(0x60);
	if (!(scancode & 0b10000000))
		putc(scancodetoascii[scancode]);
}

void initkeyboard() {
	addPicFunc(1, keyStateChanged);
}
