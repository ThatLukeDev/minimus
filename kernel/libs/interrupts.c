#define PIC1 0x20 // master pic
#define PIC2 0xa0 // slave pic

#define PIC1_OFFSET 0x20
#define PIC2_OFFSET (PIC1_OFFSET+8)

#include "ioutils.h"

#include "console.h" //temp

struct idtelement {
	unsigned short offset1; // offset 0-15
	unsigned short selector; // a code segment selector in gdt
	unsigned char base; // segment base (reserved) + ist
	unsigned char attr; // gate type, dpl, and leftmost bit must be 1
	unsigned short offset2; // offset 16-31
};

extern void* idtaddr;

// https://en.wikipedia.org/wiki/Interrupt_descriptor_table
void initidtelement(unsigned int num, unsigned int func, unsigned char trap) {
	struct idtelement* element = (struct idtelement*)(idtaddr+num*8);
	element->base = 0;
	element->selector = 8;
	element->attr = 0b10001110 | trap;
	element->offset1 = (unsigned short)(func);
	element->offset2 = (unsigned short)(func >> 16);
}

void sendeoi(unsigned char reg) {
	if (reg >= 8) {
		outb(PIC2, 0x20);
	}
	outb(PIC1, 0x20);
}

// https://wiki.osdev.org/8259_PIC#Programming_the_PIC_chips
void initpic() {
	// save masks
	unsigned char mask1 = inb(PIC1+1);
	unsigned char mask2 = inb(PIC2+1);

	// each wait allows PIC to process

	// set initialisation command for cascade (master and slave) (icw1)
	outb(PIC1, 0x11);
	iowait();
	outb(PIC2, 0x11);
	iowait();

	// set vector offsets (icw2)
	outb(PIC1+1, PIC1_OFFSET);
	iowait();
	outb(PIC2+1, PIC2_OFFSET);
	iowait();

	// inform master of slave pic (icw3)
	outb(PIC1+1, 0b0100);
	iowait();
	// inform slave of slave pic (icw3)
	outb(PIC2+1, 0b0010);
	iowait();

	// enable 8086 mode (icw4)
	outb(PIC1+1, 0b0001);
	iowait();
	outb(PIC2+1, 0b0001);
	iowait();

	// restore masks
	outb(PIC1+1, mask1);
	outb(PIC2+1, mask2);
}

void enablepic(unsigned char irq) {
	unsigned short port = PIC1+1;

	if (irq >= 8) {
		port = PIC2+1;
		irq -= 8;
	}

	unsigned char val = inb(port) | (1 << irq); // add mask bit (set 1)
	outb(port, val);
}

void disablepic(unsigned char irq) {
	unsigned short port = PIC1+1;

	if (irq >= 8) {
		port = PIC2+1;
		irq -= 8;
	}

	unsigned char val = inb(port) & ~(1 << irq); // remove mask bit (set 0)
	outb(port, val);
}

unsigned short irqreg(int cmd) {
	outb(PIC1, cmd);
	outb(PIC2, cmd);
	return (inb(PIC2) << 8) | inb(PIC1);
}

extern unsigned int _idt32;
void idt32() {
	printf("Interrupt\n");
	sendeoi(32-PIC1_OFFSET);
}

extern unsigned int _idt33;
void idt33() {
	printf("Interrupt\n");
	sendeoi(33-PIC1_OFFSET);
}

extern void initidtasm();
void initidt() {
	initpic();

	initidtelement(32, (unsigned int)&_idt32, 0);
	initidtelement(33, (unsigned int)&_idt33, 0);

	initidtasm();

	enablepic(0);
	enablepic(1);

	for (int i = 0; i < 1000; i++)
		iowait();

	printf("%x\n", irqreg(0x0a));
	printf("%x\n", irqreg(0x0b));
}
