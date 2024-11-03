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

	for (int i = 1; i <= 10; i++) {
		printf("%d\n", i);
		pitsleep(1);
	}
}
