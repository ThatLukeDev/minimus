#include "disk.h"
#include "strutils.h"
#include "memory.h"

#define PAGEADDRDISK 0x5000

struct filePage {
	unsigned long address;
	unsigned long size;
	char name;
};
#define filePageSize 20

struct filePage* pageaddr;

struct filePage* fileDescriptor(char* filename) {
	__asm__ volatile ("int $82");
	pageaddr = *(struct filePage**)0x1000;

	struct filePage* ptr = pageaddr;

	while (ptr->address) {
		if (!strcmp((char*)(&(ptr->name)+1), filename)) {
			return ptr;
		}
		ptr = (struct filePage*)((unsigned char*)ptr + strlen(&(ptr->name)) + filePageSize);
	}

	return (struct filePage*)0;
}

void* fileRead(char* filename) {
	struct filePage* descriptor = fileDescriptor(filename);

	if (descriptor)
		return diskRead(descriptor->address, descriptor->size);
	else
		return (void*)0;
}

void fileExec(char* filename, char* args) {
	char* instructions = fileRead(filename);

	*(char**)0x1000 = args;

	__asm__ volatile ("call %0" : : "r"(instructions));

	free(instructions);
}

void fileDelete(char* filename) {
	struct filePage* descriptor = fileDescriptor(filename);
	if (!descriptor)
		return;
	unsigned int len = strlen(&(descriptor->name)) + filePageSize;
	unsigned char* ptr = (unsigned char*)descriptor;

	unsigned int conseqZero = 0;
	for (unsigned long i = 0; conseqZero < len; i++) {
		ptr[i] = ptr[i + len];
		if (ptr[i] == 0)
			conseqZero++;
		else
			conseqZero = 0;
	}
}

void fileWrite(char* filename, unsigned char* buffer, unsigned long size) {
	__asm__ volatile ("int $82");
	pageaddr = *(struct filePage**)0x1000;

	fileDelete(filename);

	struct filePage* descriptor = pageaddr;
	unsigned long descaddr = 0;

	while (descriptor->address) {
		descaddr = descriptor->address + descriptor->size;
		descriptor = (struct filePage*)((unsigned char*)descriptor + strlen(&(descriptor->name)) + filePageSize);
	}

	descriptor->address = descaddr;
	descriptor->size = size;
	memcpy(&(descriptor->name), filename, strlen(filename));

	diskWriteSector(PAGEADDRDISK / 512, 0, (void*)pageaddr);

	diskWrite(descriptor->address, size, buffer);
}

char** fileList() {
	__asm__ volatile ("int $82");
	pageaddr = *(struct filePage**)0x1000;

	int sizeTrack = sizeof(void*);
	char** wordList = malloc(sizeTrack);
	wordList[0] = (char*)0;

	struct filePage* ptr = pageaddr;

	while (ptr->address) {
		sizeTrack += sizeof(void*);
		wordList = realloc(wordList, sizeTrack);
		wordList[sizeTrack / sizeof(void*) - 2] = &(ptr->name)+1;
		wordList[sizeTrack / sizeof(void*) - 1] = 0;
		ptr = (struct filePage*)((unsigned char*)ptr + strlen(&(ptr->name)) + filePageSize);
	}

	return wordList;
}
