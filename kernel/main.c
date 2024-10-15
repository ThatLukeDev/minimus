#include "memory.h"
#include "console.h"

void main() {
	initheap();
	clrscr();

	char str1[] = "Hello %s!\nNum is %d.";
	char str2[] = "World";
	int num = -4123;
	printf(str1, str2, num);
}
