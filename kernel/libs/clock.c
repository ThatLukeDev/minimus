#define CLOCK_FREQ 291.304199219d // middle ground, can go 170 days before overflow

#include "pic.h"
#include "ioutils.h"

unsigned long ticks = 0;
double runtime = 0;

void pitsleep(double time) {
	double last = runtime;

	while (runtime < last + time) {
		iowait();
	}

	return;
}

void pitint() {
	ticks++;
	runtime = ticks / CLOCK_FREQ;
}

void initclock() {
	outb(0x40, 0);
	outb(0x40, 16); // 291.304199219 hz
	addPicFunc(0, pitint);
}
