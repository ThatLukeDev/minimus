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

	printf("Welcome to Minimus! Type 'help' for a list of commands\n");
	printf("(.min files are executable, but you can call them what you like)\n");
	printf("(executing a non-executable file will crash)\n");

	while (1) {
		printf("> ");
		char* input = gets();

		if (!strcmp(input, "help")) {
			printf("ls            Lists all files\n");
			printf("[name]        Execute [name]\n");
		}
		else if (!strcmp(input, "ls")) {
			char** files = fileList();

			for (int i = 0; files[i] != 0; i++) {
				printf("%s\n", files[i]);
			}

			free(files);
		}
		else {
			char** files = fileList();

			for (int i = 0; files[i] != 0; i++) {
				if (!strcmp(files[i], input)) {
					fileExec(input);
				}
			}

			free(files);
		}

		free(input);
	}
}
