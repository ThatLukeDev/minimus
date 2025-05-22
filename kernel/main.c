#include "ioutils.h"
#include "strutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"
#include "pic.h"
#include "clock.h"
#include "vga.h"
#include "mouse.h"
#include "disk.h"
#include "file.h"
#include "graphics.h"
#include "image.h"

void main() {
	initheap();
	initconsole();
	clrscr();
	initvga();
	initidt();
	initclock();
	initfs();

	inttest();

	printf("Welcome to Minimus! Type 'help' for a list of commands\n");

	while (1) {
		printf("> ");
		char* input = gets();

		char* args = 0;

		for (int i = 0; i < strlen(input); i++) {
			if (input[i] == ' ') {
				input[i] = 0;
				args = input + i + 1;
				break;
			}
		}

		char** files = fileList();

		char foundFile = 0;
		for (int i = 0; files[i] != 0; i++) {
			if (!strcmp(files[i], input)) {
				if (files[i][-1] == '1') {
					fileExec(input, args);
					foundFile = 1;
				}
				else {
					printf("File not executable\n");
				}
			}
		}
		if (!foundFile) {
			printf("Command not found\n");
		}

		free(files);

		free(input);
	}
}
