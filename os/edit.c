#include "file.h"
#include "strutils.h"
#include "console.h"
#include "keyboard.h"
#include "memory.h"

int main() {
	char scancodelookup[256] = {
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

	char* args = *(char**)0x1000;
	if (!args || !strcmp(args, "-h")) {
		printf("USAGE: edit [FILENAME]\n");

		printf("Edits or creates a file\n");

		return -1;
	}
	char* filename = args;

	showConsoleOutput(0);
	clrscr();
	char* keyStates = getKeyStates();
	char* prevKeyStates = malloc(128);
	memcpy(prevKeyStates, keyStates, 128);

	while (1) {
		for (int i = 0; i < 128; i++) {
			if (prevKeyStates[i] == keyStates[i])
				continue;
			prevKeyStates[i] = keyStates[i];

			if (!keyStates[i])
				continue;

			char asciicode = scancodelookup[i];
			if (!asciicode)
				continue;

			if (!keyStates[SC_CTRL]) {


				continue;
			}

			if (!keyStates[SC_SHIFT]) {
				if (asciicode == '-')
					asciicode = '_';
				else if (asciicode == '#')
					asciicode = '~';
				else if (asciicode == '\'')
					asciicode = '@';
				else if (asciicode < '0')
					asciicode += 16;
				else if (asciicode >= 'a' && asciicode <= 'z')
					asciicode -= 32;
				else if (asciicode >= '1' && asciicode <= '5' && asciicode != '3')
					asciicode -= 16;
				else if (asciicode >= '7' && asciicode <= '9' && asciicode != '8')
					asciicode -= 17;
				else if (asciicode >= '[' && asciicode <= ']')
					asciicode += 32;
				else if (asciicode == '6')
					asciicode = '^';
				else if (asciicode == '8')
					asciicode = '*';
				else if (asciicode == '0')
					asciicode = ')';
				else if (asciicode == ';')
					asciicode = ':';
				else if (asciicode == '=')
					asciicode = '+';
			}

			putc(asciicode);
		}
	}

	return 0;
}
