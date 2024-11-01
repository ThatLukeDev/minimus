#include "ioutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"
#include "pic.h"

void main() {
	clrscr();
	initheap();
	initidt();

	printf("Enter a string: ");
	char* str = gets();
	printf("You entered %s\n", str);
}
