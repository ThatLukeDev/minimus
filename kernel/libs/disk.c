#include "ioutils.h"
#include "memory.h"

void diskWait() {
	for (int i = 0; i < 15; i++) {
		inb(0x1f7);
	}
	unsigned char status = inb(0x1f7);
	while ((status & 0b10000000 && !(status & 0b1000)))
		continue;
}

void* diskReadSector(unsigned int lba, unsigned char sectors) {
	unsigned short mallocSec = sectors;
	if (mallocSec == 0)
		mallocSec = 256;
	unsigned char* buffer = malloc(mallocSec * 512);

	outb(0x1f6, 0xe0 | ((lba >> 24) & 0x0f)); // drive and upper 4 bits of lba
	outb(0x1f1, 0); // ignored but necessary on some systems
	outb(0x1f2, sectors);
	outb(0x1f3, lba); // lower 8 bits
	outb(0x1f4, lba >> 8); // mid lower 8 bits
	outb(0x1f5, lba >> 16); // mid upper 8 bits
	outb(0x1f7, 0x20); // read flag

	for (int sector = 0; sector < mallocSec; sector++) {
		diskWait();

		for (int i = 0; i < 256; i++) {
			*(unsigned short*)(buffer + sector * 512 + i * 2) = inw(0x1f0);
		}
	}

	return buffer;
}

void diskWriteSector(unsigned int lba, unsigned char sectors, unsigned char* buffer) {
	unsigned short mallocSec = sectors;
	if (mallocSec == 0)
		mallocSec = 256;

	outb(0x1f6, 0xe0 | ((lba >> 24) & 0x0f)); // drive and upper 4 bits of lba
	outb(0x1f1, 0); // ignored but necessary on some systems
	outb(0x1f2, sectors);
	outb(0x1f3, lba); // lower 8 bits
	outb(0x1f4, lba >> 8); // mid lower 8 bits
	outb(0x1f5, lba >> 16); // mid upper 8 bits
	outb(0x1f7, 0x30); // write flag

	for (int sector = 0; sector < mallocSec; sector++) {
		diskWait();

		for (int i = 0; i < 256; i++) {
			outw(0x1f0, *(unsigned int*)(buffer + sector * 512 + i * 2));
		}
	}
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
