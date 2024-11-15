#define CLOCK_FREQ 291304 // middle ground, can go 170 days before overflow (given in millihz)

#include "pic.h"
#include "ioutils.h"

unsigned long ticks = 0;
unsigned long runtime = 0;

void pitsleep(unsigned long milliseconds) {
	unsigned long desired = runtime + milliseconds;

	while (1) {
		if (runtime > desired) {
			return;
		}
		iowait();
	}
}

void pitint() {
	ticks++;
	runtime = ticks * 1000000 / CLOCK_FREQ;
}

void initclock() {
	outb(0x40, 0);
	outb(0x40, 16); // 291.304199219 hz
	addPicFunc(0, pitint);
}
