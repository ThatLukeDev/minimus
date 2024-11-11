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

	//drawchar('a', 0, 0);
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 200; y++)
			drawpixel(x, x, y);
}
