#define MAX_CLOCK_FREQ 1193182
#define CLOCK_FREQ 1000
#define CLOCK_DIVISIONS (MAX_CLOCK_FREQ / CLOCK_FREQ)

#include "pic.h"
#include "ioutils.h"

unsigned long ticks = 0;

void pitsleep(unsigned long milliseconds) {
	unsigned long desired = ticks + milliseconds * CLOCK_DIVISIONS / 1000;

	while (1) {
		if (ticks > desired) {
			return;
		}
	}
}

void pitint() {
	ticks++;
}

void initclock() {
	outb(0x40, (CLOCK_DIVISIONS) & 0xff);
	outb(0x40, (CLOCK_DIVISIONS >> 8) & 0xff);
	addPicFunc(0, pitint);
}
