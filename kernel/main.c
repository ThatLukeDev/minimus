#include "bochs.h"

#include "ioutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"
#include "pic.h"
#include "clock.h"
#include "vga.h"

void main() {
	initheap();
	clrscr();
	initvga();
	initidt();
	initclock();

	printf("Hello World!");
}
