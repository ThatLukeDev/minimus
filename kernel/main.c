#include "ioutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"
#include "pic.h"
#include "clock.h"
#include "vga.h"

void main() {
	clrscr();
	initheap();
	initidt();
	initclock();
	initvga();

	drawchar(0, 0, 'a');
	drawchar(1, 0, 'b');
	drawchar(2, 0, 'c');
}
