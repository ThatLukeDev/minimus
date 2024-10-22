#include "memory.h"
#include "console.h"
#include "interrupts.h"

void main() {
	clrscr();
	initheap();
	initidt();
	//clrscr();

	//int x = 1 / 0;
}
