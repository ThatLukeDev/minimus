#include "ioutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"

void main() {
	clrscr();
	initheap();
	initidt();
}
