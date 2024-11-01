#include "console.h"

// interrupts.h
void interrupthandler(unsigned char interrupt) {
	if (interrupt == 33)
		printf("\n");
	printf("%d", interrupt);
	if (interrupt == 33)
		printf("\n");
}
