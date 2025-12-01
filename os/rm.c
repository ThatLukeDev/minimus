#include "console.h"
#include "memory.h"
#include "file.h"
#include "strutils.h"

int main() {
	char* args = *(char**)0x1000;

	if (!args || !strcmp(args, "-h")) {
		printf("USAGE: rm [FILENAME]\n");

		return -1;
	}

	fileDelete(args);
	free(args);

	return 0;
}
