#include "pic.h"
#include "ioutils.h"

#include "console.h" //tmp

void mouseStateChanged() {
	__asm__ volatile ("hlt");
}

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

void initmouse() {
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

	sendMouse(0xf6, 1);
	sendMouse(0xf4, 1);

	__asm__ volatile ("sti");
}
