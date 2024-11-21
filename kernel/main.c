#include "ioutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"
#include "pic.h"
#include "clock.h"
#include "vga.h"
#include "mouse.h"
#include "disk.h"

void main() {
	initheap();
	initconsole();
	clrscr();
	initvga();
	initidt();
	initclock();
	initmouse();

	unsigned char* tmp = diskRead(500, 0x1000);

	printf("0x1f5: ");
	for (int i = 0x1f5 - 500; i < 0x205 - 500; i++)
		printf("%x ", tmp[i]);
	printf("\n");
	printf("0x400: ");
	for (int i = 0x400 - 500; i < 0x410 - 500; i++)
		printf("%x ", tmp[i]);
	printf("\n");
	printf("0x1000: ");
	for (int i = 0x1000 - 500; i < 0x1010 - 500; i++)
		printf("%x ", tmp[i]);
	printf("\n");

	printf("\n");
	printf("Setting all to sequential");
	for (int i = 0; i < 0x1000; i++) {
		tmp[i] = (unsigned char)(i + 500);
	}
	diskWrite(500, 0x1000, tmp);
	printf("\n");

	printf("0x1f5: ");
	for (int i = 0x1f5 - 500; i < 0x205 - 500; i++)
		printf("%x ", tmp[i]);
	printf("\n");
	printf("0x400: ");
	for (int i = 0x400 - 500; i < 0x410 - 500; i++)
		printf("%x ", tmp[i]);
	printf("\n");
	printf("0x1000: ");
	for (int i = 0x1000 - 500; i < 0x1010 - 500; i++)
		printf("%x ", tmp[i]);
	printf("\n");
}
