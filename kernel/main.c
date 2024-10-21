#include "memory.h"
#include "console.h"
#include "interrupts.h"

struct idtelement* idtptrtmp = (struct idtelement*)0x10000;

void main() {
	initheap();
	initidt();
	clrscr();

	unsigned short offset1 = idtptrtmp->offset1;
	int xxxx1111=0;
	unsigned short offset2 = idtptrtmp->offset2;
	int xxxx1112=0;
	printf("%d %d", offset1, offset2);
}
