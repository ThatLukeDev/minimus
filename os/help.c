#include "console.h"
#include "memory.h"
#include "file.h"

int main() {
	char* text = *(char**)0x1000;

	if (text) {
		fileExec(text, "-h");
	}
	else {
		printf("USAGE: help [command]\n");

		printf("Runs the program without arguments,\n");
		printf("which normally gives a help screen.\n");

		printf("\n");

		printf("COMMANDS:\n");

		char** files = fileList();

		for (int i = 0; files[i] != 0; i++) {
			if (files[i][-1] == '1')
				printf("%s\n", files[i]);
		}

		free(files);

		return -1;
	}

	return 0;
}
