#include "memory.h"
#include "console.h"
#include "interrupts.h"

void main() {
	initheap();
	initidt();
	clrscr();

	printf("a");
}
