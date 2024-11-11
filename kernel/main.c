#include "ioutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"
#include "pic.h"
#include "clock.h"

void main() {
	clrscr();
	initheap();
	initidt();
	initclock();

	*((unsigned int*)0xa0000) = 0;
	printf("%d", *(unsigned int*)0xa0000);
}
