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

	char* keyStates = getKeyStates();
	char* prevKeyStates = malloc(128);
	memcpy(prevKeyStates, keyStates, 128);

	char* filename = malloc(strlen(args));
	memcpy(filename, args, strlen(args));

	int filestorelen = strlen(filename) + 2;
	char* filestore = malloc(filestorelen);
	filestore[0] = '0';
	memcpy(filestore + 1, filename, filestorelen - 1);

	char* buf = fileRead(filestore);
	unsigned long bufSize = 0;
	if (buf) {
		bufSize = strlen(buf);
	}
	else {
		bufSize = 32;
		buf = malloc(32);
	}

	showConsoleOutput(0);
	clrscr();

	char iterpollkeyboard = 1;

	while (iterpollkeyboard) {
		for (int i = 0; i < 64; i++) {
			if (prevKeyStates[i] == keyStates[i])
				continue;
			prevKeyStates[i] = keyStates[i];

			if (!keyStates[i])
				continue;

			char asciicode = scancodelookup[i];
			if (!asciicode)
				continue;

			if (!keyStates[SC_CTRL]) {
				if (i == SC_W || i == SC_S || i == SC_X) {
					fileWrite(filestore, buf, strlen(buf) + 1);
				}
				if (i == SC_Q || i == SC_C || i == SC_X) {
					iterpollkeyboard = 0;
				}

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

			if (strlen(buf) > bufSize - 2) {
				bufSize *= 2;
				realloc(buf, bufSize);
			}
			unsigned long buflen = strlen(buf);
			buf[buflen] = (char)asciicode;
			buf[buflen+1] = '\0';

			clrscr();
			printf("%s", buf);
		}
	}

	clrscr();
	showConsoleOutput(1);

	return 0;
}
