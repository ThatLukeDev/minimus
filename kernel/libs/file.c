#include "disk.h"
#include "strutils.h"
#include "memory.h"

#define PAGEADDRDISK 0x5000

struct filePage {
	unsigned long address;
	unsigned long size;
	char name;
};

struct filePage* pageaddr;

struct filePage* fileDescriptor(char* filename) {
	struct filePage* ptr = pageaddr;

	while (ptr->address) {
		if (!strcmp(&(ptr->name), filename)) {
			return ptr;
		}
		ptr += strlen(&(ptr->name)) + 17;
	}

	return (struct filePage*)0;
}

void* fileRead(char* filename) {
	struct filePage* descriptor = fileDescriptor(filename);

	return diskRead(descriptor->address, descriptor->size);
}

void fileDelete(char* filename) {
	struct filePage* descriptor = fileDescriptor(filename);
	if (!descriptor)
		return;
	unsigned int len = strlen(&(descriptor->name)) + 17;
	unsigned char* ptr = (unsigned char*)descriptor;

	unsigned int conseqZero = 0;
	for (unsigned long i = 0; conseqZero < len; i++) {
		ptr[i] = ptr[i + len];
		if (ptr[i] == 0)
			conseqZero++;
		else
			conseqZero = 0;
	}

	diskWriteSector(PAGEADDRDISK / 512, 0, (void*)pageaddr);
}

void fileWrite(char* filename, unsigned char* buffer, unsigned long size) {
	struct filePage* descriptor = pageaddr;
	unsigned long descaddr = 0;

	while (descriptor->address) {
		descaddr = descriptor->address + descriptor->size;
		descriptor += strlen(&(descriptor->name)) + 17;
	}

	descriptor->address = descaddr;
	descriptor->size = size;
	memcpy(filename, &(descriptor->name), strlen(filename));

	diskWriteSector(PAGEADDRDISK / 512, 0, (void*)pageaddr);

	diskWrite(descriptor->address, size, buffer);
}

void initfs() {
	pageaddr = (struct filePage*)diskReadSector(PAGEADDRDISK / 512, 0);
	pageaddr->address = PAGEADDRDISK + 256 * 512;
	pageaddr->size = 0;
	pageaddr->name = 0;
}
