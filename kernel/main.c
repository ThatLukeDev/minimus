#include "memory.h"
#include "console.h"

void main() {
	initheap();
	clrscr();

	char str[] = "Hello World!";
	puts(str);
}
