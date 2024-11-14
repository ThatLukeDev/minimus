#include "bochs.h"

#include "ioutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"
#include "pic.h"
#include "clock.h"
#include "vga.h"

void main() {
	clrscr();
	initidt();
	initheap();
	initclock();
	bochsLB();
	initvga();
	bochsLB();

	printf("hi");

	while (1) continue;
}
