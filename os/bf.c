#include "file.h"
#include "strutils.h"
#include "console.h"
#include "keyboard.h"
#include "memory.h"
#include "graphics.h"

#define TAPE_SIZE 1024

int main() {
	char* args = *(char**)0x1000;
	if (!args || !strcmp(args, "-h")) {
		printf("USAGE: bf [FILENAME]\n");

		printf("A very basic turing-complete BF interpreter\n");

		return -1;
	}

	char* code = fileRead(args);

	if (!code) {
		printf("No code supplied\n");
		return -1;
	}

	char* keyStates = getKeyStates();
	char* tape = malloc(TAPE_SIZE);
	memset(tape, 0, TAPE_SIZE);
	int ptr = 0;

	for (int i = 0; i < strlen(code); i++) {
		if (!keyStates[SC_CTRL] && !keyStates[SC_C])
			return -1;

		ptr = ((ptr % TAPE_SIZE) + TAPE_SIZE) % TAPE_SIZE;

		if (code[i] == '+')
			tape[ptr]++;
		else if (code[i] == '-')
			tape[ptr]--;
		else if (code[i] == '<')
			ptr--;
		else if (code[i] == '>')
			ptr++;
		else if (code[i] == ',')
			tape[ptr] = getc();
		else if (code[i] == '.')
			if (tape[ptr] == '\n')
				printf("\n");
			else
				putc(tape[ptr]);
		else if (code[i] == '[') {
			if (tape[ptr] == 0) {
				for (int count = 1; count > 0; i++) {
					if (code[i+1] == '[')
						count++;
					if (code[i+1] == ']')
						count--;
				}
			}
		}
		else if (code[i] == ']') {
			for (int count = 1; count > 0; i--) {
				if (code[i-1] == ']')
					count++;
				if (code[i-1] == '[')
					count--;
			}
			i--;
		}
	}

	return 0;
}
