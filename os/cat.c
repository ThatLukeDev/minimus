#include "console.h"
#include "memory.h"
#include "file.h"
#include "strutils.h"

int main() {
	char* args = *(char**)0x1000;

	if (!args || !strcmp(args, "-h")) {
		printf("USAGE: cat [FILENAME]\n");

		return -1;
	}

	char* content = fileRead(args);

	printf("%s\n", content);

	free(content);
	free(args);

	return 0;
}
