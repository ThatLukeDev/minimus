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
		ptr = ((ptr % TAPE_SIZE) + TAPE_SIZE) % TAPE_SIZE;
		if (code[i] == '+')
			tape[ptr]++;
		if (code[i] == '-')
			tape[ptr]--;
		if (code[i] == '<')
			ptr--;
		if (code[i] == '>')
			ptr++;
		if (code[i] == ',')
			tape[ptr] = getc();
		if (code[i] == '.')
			putc(tape[ptr]);
		if (code[i] == '[') {
			if (tape[ptr] == 0) {
				for (int count = 1; count > 0; i++) {
					if (tape[i+1] == '[')
						count++;
					if (tape[i+1] == ']')
						count--;
				}
			}
		}
	}

	return 0;
}
