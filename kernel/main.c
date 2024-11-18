#include "bochs.h"

#include "ioutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"
#include "pic.h"
#include "clock.h"
#include "vga.h"
#include "mouse.h"

void main() {
	initheap();
	initconsole();
	clrscr();
	initvga();
	initidt();
	initclock();
	initmouse();

	printf("CTRL + SCROLLBTN to enable mouse\non bochs.\n");

	while (1) {
		unsigned char r = 0xff;
		unsigned char g = 0xff;
		unsigned char b = 0xff;
		if (mouseRight)
			r = 0x00;
		if (mouseLeft)
			b = 0x00;
		drawpixel(mouseX, mouseY, r, g, b);
	}
}
