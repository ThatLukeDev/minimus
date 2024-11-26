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

void main() {
	initheap();
	initconsole();
	clrscr();
	initvga();
	initidt();
	initclock();
	initmouse();
	initfs();

	while (1) {
		printf("Filename: ");
		char* filename = gets();
		char* output = fileRead(filename);

		if (output)
			printf("%s\n", output);
		else {
			char* buffer = gets();
			fileWrite(filename, buffer, strlen(buffer)+1);
		}
	}
}
