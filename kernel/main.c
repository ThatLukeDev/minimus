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

	char* str = "Hello World!\nName: ";
	*(unsigned int*)0x1000 = (unsigned int)str;
	__asm__ volatile ("int $71");

	__asm__ volatile ("int $73");

	printf("Hello %s!\n", (char*)(*(unsigned int*)0x1000));
}
