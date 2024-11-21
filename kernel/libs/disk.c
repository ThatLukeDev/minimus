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
	unsigned char* buffer = malloc(sectors * 512);

	outb(0x1f6, 0xe0 | ((lba >> 24) & 0x0f)); // drive and upper 4 bits of lba
	outb(0x1f1, 0); // ignored but necessary on some systems
	outb(0x1f2, sectors);
	outb(0x1f3, lba); // lower 8 bits
	outb(0x1f4, lba >> 8); // mid lower 8 bits
	outb(0x1f5, lba >> 16); // mid upper 8 bits
	outb(0x1f7, 0x20); // read flag

	for (int sector = 0; sector < sectors; sector++) {
		diskWait();

		for (int i = 0; i < 256; i++) {
			*(unsigned short*)(buffer + sector * 512 + i * 2) = inw(0x1f0);
		}
	}

	return buffer;
}

void* diskWriteSector(unsigned int lba, unsigned char sectors, unsigned char* buffer) {
	outb(0x1f6, 0xe0 | ((lba >> 24) & 0x0f)); // drive and upper 4 bits of lba
	outb(0x1f1, 0); // ignored but necessary on some systems
	outb(0x1f2, sectors);
	outb(0x1f3, lba); // lower 8 bits
	outb(0x1f4, lba >> 8); // mid lower 8 bits
	outb(0x1f5, lba >> 16); // mid upper 8 bits
	outb(0x1f7, 0x30); // write flag

	for (int sector = 0; sector < sectors; sector++) {
		diskWait();

		for (int i = 0; i < 256; i++) {
			outw(0x1f0, *(unsigned int*)(buffer + sector * 512 + i * 2));
		}
	}

	return buffer;
}
