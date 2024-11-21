#ifndef DISK_LIB
#define DISK_LIB

extern void* diskReadSector(unsigned int lba, unsigned char sectors);
extern void* diskWriteSector(unsigned int lba, unsigned char sectors, unsigned char* buffer);

extern void* diskRead(unsigned long addr, unsigned long size);
extern void* diskWrite(unsigned long addr, unsigned long size, unsigned char* buffer);

#endif
