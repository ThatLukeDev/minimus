#ifndef FILE_LIB
#define FILE_LIB

extern void* fileRead(char* filename);
extern void fileWrite(char* filename, unsigned char* buffer, unsigned long size);
extern void fileDelete(char* filename);
extern char** fileList();

extern void fileExec(char* filename);

#endif
