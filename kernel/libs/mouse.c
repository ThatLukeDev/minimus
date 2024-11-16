#include "pic.h"
#include "ioutils.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

unsigned char recieveMouse() {
	while (!(inb(0x64) & 0b0001)) continue; // wait for read flag
	return inb(0x60); // output
}

void sendMouse(unsigned char command, unsigned char ack) {
	while (inb(0x64) & 0b0010) continue; // wait for write flag
	outb(0x64, 0xd4); // address mouse
	while (inb(0x64) & 0b0010) continue; // wait for write flag
	outb(0x60, command); // send command
	if (ack) {
		while (recieveMouse() != 0xfa) continue; // wait for ack
	}
}

int mouseX;
int mouseY;
unsigned char mouseLeft;
unsigned char mouseRight;

void mouseStateChanged() {
	unsigned char misc = recieveMouse();
	unsigned char dx = recieveMouse();
	unsigned char dy = recieveMouse();

	mouseLeft = misc & 0b00000001;
	mouseRight = misc & 0b00000010;

	if (misc & 0b11000000) { // mouse overflow
		dx = 0;
		dy = 0;
	}

	int signdx = dx;
	int signdy = dy;

	if (misc & 0b00010000) // x sign bit
		signdx |= ~0b0011;
	if (misc & 0b00100000) // y sign bit
		signdy |= ~0b0011;

	signdy *= -1; // flipped

	mouseX += signdx;
	mouseY += signdy;

	if (mouseX < 0)
		mouseX = 0;
	if (mouseX > SCREEN_WIDTH)
		mouseX = SCREEN_WIDTH;
	if (mouseY < 0)
		mouseY = 0;
	if (mouseY > SCREEN_HEIGHT)
		mouseY = SCREEN_HEIGHT;
}

void initmouse() {
	mouseLeft = 0;
	mouseRight = 0;
	mouseX = 0;
	mouseY = 0;

	addPicFunc(12, mouseStateChanged);

	__asm__ volatile ("cli");

	while (inb(0x64) & 0b0010) continue; // wait for write flag
	outb(0x64, 0x20); // read compaq
	unsigned char compaq = recieveMouse();

	compaq &= 0b11011111;
	compaq |= 0b00000010;

	while (inb(0x64) & 0b0010) continue; // wait for write flag
	outb(0x64, 0x60); // write compaq
	while (inb(0x64) & 0b0010) continue; // wait for write flag
	outb(0x60, compaq); // write compaq

	sendMouse(0xff, 1);
	sendMouse(0xf6, 1);
	sendMouse(0xf4, 1);

	__asm__ volatile ("sti");
}
