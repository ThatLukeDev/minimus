#include "disk.h"
#include "strutils.h"

#define PAGEADDR 0x5000

struct filePage {
	unsigned long address;
	unsigned long size;
	char name;
};

struct filePage* fileDescriptor(char* filename) {
	struct filePage* ptr = (struct filePage*)PAGEADDR;

	while (ptr->address) {
		if (!strcmp(&(ptr->name), filename)) {
			return ptr;
		}
		ptr += strlen(&(ptr->name)) + 3;
	}

	return 0;
}

void* fileRead(char* filename, unsigned long* sizeOut) {
}

void fileWrite(char* filename, unsigned char* buffer, unsigned long size) {
}
