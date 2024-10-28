#include "memory.h"
#include "console.h"
#include "interrupts.h"

void main() {
	clrscr();
	initheap();
	initidt();
	//clrscr();

	printf("a");
	__asm__ volatile ("int $0x21");
}
