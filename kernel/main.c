#include "memory.h"
#include "console.h"
#include "interrupts.h"

void main() {
	initheap();
	initidt();
	clrscr();

	printf("a");

	int x = 1 / 0;

	printf("a");
}
