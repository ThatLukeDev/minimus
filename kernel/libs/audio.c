#include "ioutils.h"
#include "pic.h"
#include "clock.h"

void audiopicChanged() {
}

void initaudio() {
	addPicFunc(5, audiopicChanged);

	outb(0x224, 0x80);
	outb(0x224, 0x02); // set irq 5
}

void playaudio(void* sound, unsigned short length) {
	// reset dsp
	outb(0x226, 1);
	pitsleep(1);
	outb(0x226, 0);

	// disable
	outb(0x0a, 0x05);

	// flipflop port
	outb(0x0c, 0);

	// transfer mode
	outb(0x0b, 0x48);

	// address
	outb(0x83, (unsigned char)((unsigned int)sound >> 16));
	outb(0x02, (unsigned char)((unsigned int)sound));
	outb(0x02, (unsigned char)((unsigned int)sound >> 8));

	// length
	outb(0x03, (unsigned char)length);
	outb(0x03, (unsigned char)(length >> 8));

	// enable
	outb(0x0a, 0x01);
}
