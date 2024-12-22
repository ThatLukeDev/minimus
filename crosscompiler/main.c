#include "console.h"
#include "memory.h"
#include "file.h"
#include "strutils.h"

int main() {
	char* args = *(char**)0x1000;

	if (!strcmp(args, "-h")) {
		printf("USAGE: ls [TYPE?]\n");

		return -1;
	}

	char** files = fileList();

	for (int i = 0; files[i] != 0; i++) {
		if (args == 0 || files[i][-1] == args[0])
			printf("%s\n", files[i]);
	}

	free(files);

	return 0;
}
