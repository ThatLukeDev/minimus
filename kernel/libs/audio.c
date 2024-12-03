#include "ioutils.h"
#include "pic.h"
#include "clock.h"

#include "console.h" // temp
void audiopicChanged() {
	printf("a");
}

void initaudio() {
	addPicFunc(5, audiopicChanged);

	// reset dsp
	outb(0x226, 1);
	pitsleep(1);
	outb(0x226, 0);

	// speaker on
	outb(0x22c, 0xd1);

	// set irq 5
	outb(0x224, 0x80);
	outb(0x225, 0x02);
}

void playaudio(void* sound, unsigned short length, unsigned long samples) {
	sound = 0;

	// disable
	outb(0x0a, 0x05);

	// flipflop port
	outb(0x0c, 1);

	// transfer mode
	outb(0x0b, 0x49);

	// address
	outb(0x83, (unsigned char)((unsigned int)sound >> 16));
	outb(0x02, (unsigned char)((unsigned int)sound));
	outb(0x02, (unsigned char)((unsigned int)sound >> 8));

	// length
	outb(0x03, (unsigned char)length);
	outb(0x03, (unsigned char)(length >> 8));

	// enable
	outb(0x0a, 0x01);

	unsigned int period = 65536 - (256000000 / samples);

	// time constant
	outb(0x22c, 0x40);
	outb(0x22c, period);

	// sound bits
	outb(0x22c, 0xc0);

	// length
	outb(0x22c, 0x0);

	outb(0x22c, (unsigned char)(length-1));
	outb(0x22c, (unsigned char)((length-1) >> 8));
}
