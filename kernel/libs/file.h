#ifndef FILE_LIB
#define FILE_LIB

extern void* fileRead(char* filename, unsigned long* sizeOut);
extern void fileWrite(char* filename, unsigned char* buffer, unsigned long size);

#endif
