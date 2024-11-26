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

	char* filename = "hwpart1.txt";
	char* filename2 = "hwpart2.txt";

	char* buf = "No ";
	fileWrite(filename, buf, strlen(buf) + 1);
	char* bufoverwrite = "Hello ";
	fileWrite(filename, bufoverwrite, strlen(bufoverwrite) + 1);
	char* buf2 = "World!";
	fileWrite(filename2, buf2, strlen(buf2) + 1);

	char* obuf1 = fileRead(filename);
	char* obuf2 = fileRead(filename2);

	printf("%s%s", obuf1, obuf2);
}
