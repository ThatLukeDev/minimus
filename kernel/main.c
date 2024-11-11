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

	drawchar('a', 0, 0);
}
