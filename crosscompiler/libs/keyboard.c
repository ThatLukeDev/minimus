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

void addKeyboardHook(void (*func)(char)) {
}

void removeKeyboardHook(void (*func)(char)) {
}