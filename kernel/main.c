#include "memory.h"
#include "console.h"

void main() {
	initheap();
	clrscr();

	char* str = "World";
	int num = -4123;
	printf("Hello %s!\nNum is %d.\n", str, num);
}
