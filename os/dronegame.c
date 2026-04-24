#include "file.h"
#include "strutils.h"
#include "console.h"
#include "keyboard.h"
#include "memory.h"
#include "graphics.h"

int main() {
	char* args = *(char**)0x1000;
	if (!strcmp(args, "-h")) {
		printf("USAGE: dronegame [OBJECTS?]\n");

		return -1;
	}

	char* keyStates = getKeyStates();
	char* prevKeyStates = malloc(128);
	memcpy(prevKeyStates, keyStates, 128);

	showConsoleOutput(0);
	clrscr();

	char iterpollkeyboard = 1;

	while (iterpollkeyboard) {
		for (int i = 0; i < 64; i++) {
			if (prevKeyStates[i] == keyStates[i])
				continue;
			prevKeyStates[i] = keyStates[i];

			if (keyStates[i])
				continue;

			if (!keyStates[SC_CTRL]) {
				if (i == SC_Q || i == SC_C || i == SC_X) {
					iterpollkeyboard = 0;
				}

				continue;
			}

			printf("%x ", i);
		}
	}

	free(prevKeyStates);
	free(args);

	clrscr();
	showConsoleOutput(1);

	return 0;
}
