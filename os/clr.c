#include "console.h"
#include "memory.h"
#include "file.h"
#include "strutils.h"

int main() {
	char* args = *(char**)0x1000;

	if (!strcmp(args, "-h")) {
		printf("USAGE: clr\n");

		printf("Clears screen.\n");

		return -1;
	}

	clrscr();

	return 0;
}
