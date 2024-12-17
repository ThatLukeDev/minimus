#include "console.h"
#include "memory.h"

int main() {
	printf("Hello World!\n");
	char* mem = malloc(1000);
	printf("1000 bytes: %x\n", mem);

	return 0;
}
