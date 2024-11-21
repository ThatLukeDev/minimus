#ifndef DISK_LIB
#define DISK_LIB

extern void* diskReadSector(unsigned int lba, unsigned char sectors);
void* diskWriteSector(unsigned int lba, unsigned char sectors, unsigned char* buffer);

#endif
