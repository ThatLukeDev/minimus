#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define BUFSIZE 0x1000000
#define FILEDIR "files"
#define PAGEADDRDISK 0x5000

struct filePage {
	unsigned int address;
	unsigned int size;
	char name;
};
#define filePageSize 20

struct filePage* pageaddr;

struct filePage* fileDescriptor(char* filename) {
	struct filePage* ptr = pageaddr;

	while (ptr->address) {
		if (!strcmp(&(ptr->name), filename)) {
			return ptr;
		}
		*((unsigned char*)&ptr) += strlen(&(ptr->name)) + filePageSize;
	}

	return (struct filePage*)0;
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

void fileWrite(char* filename, FILE* fileptr, unsigned int size) {
	fileDelete(filename);

	struct filePage* descriptor = pageaddr;
	unsigned long descaddr = 0;

	while (descriptor->address) {
		descaddr = descriptor->address + descriptor->size;
		*((unsigned char*)&descriptor) += strlen(&(descriptor->name)) + filePageSize;
	}

	descriptor->address = descaddr;
	descriptor->size = size;
	memcpy(&(descriptor->name), filename, strlen(filename));

	fread((unsigned char*)pageaddr + descriptor->address - PAGEADDRDISK, size, 1, fileptr);
}

void main() {
	pageaddr = malloc(BUFSIZE);
	for (unsigned long i = 0; i < BUFSIZE; i++) {
		((unsigned char*)pageaddr)[i] = 0;
	}
	pageaddr->address = PAGEADDRDISK + 256 * 512;
	pageaddr->size = 0;
	pageaddr->name = 0;

	DIR* d;
	struct dirent* dir;
	d = opendir(FILEDIR);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
				continue;
			printf("Compiling %s\n", dir->d_name);

			char path[strlen(dir->d_name) + 7];
			for (int i = 0; i < strlen(FILEDIR); i++) {
				path[i] = FILEDIR[i];
			}
			path[strlen(FILEDIR)] = '/';
			path[strlen(FILEDIR) + 1] = 0;
			strcat(path, dir->d_name);
			FILE* fileptr = fopen(path, "rb");

			fseek(fileptr, 0, SEEK_END);
			unsigned int size = ftell(fileptr);
			fclose(fileptr);
			fileptr = fopen(path, "rb");

			fileWrite(dir->d_name, fileptr, size);

			fclose(fileptr);
		}
		closedir(d);
	}

	FILE* fileptr = fopen("bin/blob", "wb");
	fwrite(pageaddr, BUFSIZE, 1, fileptr);
	fclose(fileptr);
}
