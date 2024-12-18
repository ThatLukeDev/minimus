#include "memory.h"

void* diskReadSector(unsigned int lba, unsigned char sectors) {
	*(unsigned int*)0x1000 = lba;
	*(unsigned char*)0x1010 = sectors;
	__asm__ volatile ("int $80");
	return (void*)(*(unsigned int*)0x1000);
}

void diskWriteSector(unsigned int lba, unsigned char sectors, unsigned char* buffer) {
	*(unsigned int*)0x1000 = lba;
	*(unsigned char*)0x1010 = sectors;
	*(unsigned int*)(0x1020) = (unsigned int)buffer;
	__asm__ volatile ("int $81");
}

void* diskRead(unsigned long addr, unsigned long size) {
	unsigned long sectorStart = addr / 512;
	unsigned long sectorEnd = (addr + size) / 512;
	unsigned long sectors = sectorEnd - sectorStart;
	unsigned long offset = addr - sectorStart * 512;

	unsigned char* buffer = malloc(size);

	unsigned long i = 0;

	for (unsigned int sector = sectorStart; sector <= sectorEnd; sector++) {
		unsigned char* current = diskReadSector(sector, 1);

		unsigned long endOfSector = (sector + 1) * 512 - addr;
		if (endOfSector > size)
			endOfSector = size;

		for (; i < endOfSector; i++) {
			buffer[i] = current[(i + offset) % 512];
		}

		free(current);
	}

	return buffer;
}

void diskWrite(unsigned long addr, unsigned long size, unsigned char* buffer) {
	unsigned int sectorStart = addr / 512;
	unsigned int sectorEnd = (addr + size) / 512;
	unsigned int sectors = sectorEnd - sectorStart;
	unsigned int offset = addr - sectorStart * 512;

	unsigned int i = 0;

	for (unsigned long sector = sectorStart; sector <= sectorEnd; sector++) {
		unsigned char* current = diskReadSector(sector, 1);

		unsigned long endOfSector = (sector + 1 - sectorStart) * 512 - offset;
		if (endOfSector > size)
			endOfSector = size;

		for (; i < endOfSector; i++) {
			current[(i + offset) % 512] = buffer[i];
		}

		diskWriteSector(sector, 1, current);
		free(current);
	}
}
