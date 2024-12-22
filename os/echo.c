#include "console.h"
#include "memory.h"
#include "file.h"
#include "strutils.h"

int main() {
	char* args = *(char**)0x1000;

	if (!strcmp(args, "-h")) {
		printf("USAGE: echo [TEXT]\n");

		return -1;
	}

	printf("%s\n", args);

	return 0;
}
