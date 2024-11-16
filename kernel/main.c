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
		unsigned char colour = 0xff;
		if (mouseRight)
			colour = 0x0f;
		if (mouseLeft)
			colour = 0xf0;
		drawpixel(mouseX, mouseY, colour);
	}
}
