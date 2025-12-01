#define PIC1 0x20 // master pic
#define PIC2 0xa0 // slave pic

#define PIC1_OFFSET 0x20
#define PIC2_OFFSET (PIC1_OFFSET+8)

#include "ioutils.h"

void interrupthandler(unsigned char interrupt);

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
	// disable interrupts
	__asm__ volatile ("cli");

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

	// masks
	outb(PIC1+1, 0xff & ~(1 << 2));
	outb(PIC2+1, 0xff);

	// enable interrupts
	__asm__ volatile ("sti");
}

void enablepic(unsigned char irq) {
	unsigned short port = PIC1+1;

	if (irq >= 8) {
		port = PIC2+1;
		irq -= 8;
	}

	unsigned char val = inb(port) & ~(1 << irq); // remove mask bit (set 0)
	outb(port, val);
}

void disablepic(unsigned char irq) {
	unsigned short port = PIC1+1;

	if (irq >= 8) {
		port = PIC2+1;
		irq -= 8;
	}

	unsigned char val = inb(port) | (1 << irq); // add mask bit (set 1)
	outb(port, val);
}

// https://pdos.csail.mit.edu/6.828/2014/readings/hardware/8259A.pdf
// 4. INTERRUPT REQUEST REGISTER (IRR) AND IN-SERVICE REGISTER (ISR)
unsigned short irqreg(int cmd) {
	outb(PIC1, cmd);
	outb(PIC2, cmd);
	return (inb(PIC2) << 8) | inb(PIC1);
}

#define idtbody(x, y) \
extern unsigned int _idt##y; \
void idt##y() { \
	interrupthandler(x); \
	sendeoi(x); \
} \

#define idthead(x, y) \
initidtelement(y, (unsigned int)&_idt##y, 0); \
enablepic(x); \

idtbody(0, 32)
idtbody(1, 33)
idtbody(3, 35)
idtbody(4, 36)
idtbody(5, 37)
idtbody(6, 38)
idtbody(7, 39)
idtbody(8, 40)
idtbody(9, 41)
idtbody(10, 42)
idtbody(11, 43)
idtbody(12, 44)
idtbody(13, 45)
idtbody(14, 46)
idtbody(15, 47)

#include "console.h"

// putc(char) -> void
extern unsigned int _idt70;
void idt70() {
	putc(*(char*)0x1000);
}

// puts(char*) -> void
extern unsigned int _idt71;
void idt71() {
	puts((char*)(*(unsigned int*)0x1000));
}

// getc() -> char
extern unsigned int _idt72;
void idt72() {
	__asm__ volatile ("sti");
	*(char*)0x1000 = getc();
	__asm__ volatile ("cli");
}

// gets() -> char*
extern unsigned int _idt73;
void idt73() {
	__asm__ volatile ("sti");
	*(unsigned int*)0x1000 = (unsigned int)gets();
	__asm__ volatile ("cli");
}

// clrscr() -> void
extern unsigned int _idt74;
void idt74() {
	clrscr();
}

// conargs() -> char*, +10 char*, +10 char*
extern unsigned int _idt75;
void idt75() {
	*(unsigned int*)0x1000 = (unsigned int)&cursor;
	*(unsigned int*)0x1010 = (unsigned int)&_typecursor;
	*(unsigned int*)0x1020 = (unsigned int)&showConsoleOutput;
}

#include "memory.h"

// malloc(int size) -> void*
extern unsigned int _idt76;
void idt76() {
	*(unsigned int*)0x1000 = (unsigned int)malloc(*(unsigned int*)0x1000);
}

// free(void* ptr) -> int
extern unsigned int _idt77;
void idt77() {
	*(unsigned int*)0x1000 = (unsigned int)free((void*)*(unsigned int*)0x1000);
}

// realloc(void* ptr, unsigned int size) -> void*
extern unsigned int _idt78;
void idt78() {
	*(unsigned int*)0x1000 = (unsigned int)realloc((void*)*(unsigned int*)0x1000, *(unsigned int*)0x1010);
}

#include "vga.h"

// drawpixel(int x, int y, char r, char g, char b) -> void
extern unsigned int _idt79;
void idt79() {
	drawpixel(*(int*)0x1000, *(int*)0x1010, *(char*)0x1020, *(char*)0x1021, *(char*)0x1022);
}

#include "disk.h"

// readdisksegment(int lba, char sectors) -> void*
extern unsigned int _idt80;
void idt80() {
	*(unsigned int*)0x1000 = (unsigned int)diskReadSector(*(unsigned int*)0x1000, *(char*)0x1010);
}

// readdisksegment(int lba, char sectors) -> void*
extern unsigned int _idt81;
void idt81() {
	diskWriteSector(*(unsigned int*)0x1000, *(char*)0x1010, (void*)*(unsigned int*)0x1020);
}

#include "file.h"

// getfilepage() -> void*
extern unsigned int _idt82;
void idt82() {
	*(unsigned int*)0x1000 = (unsigned int)pageaddr;
}

#include "keyboard.h"

// addKeyboardHook(void*()) -> void
extern unsigned int _idt83;
void idt83() {
	addKeyboardHook((void*)*(unsigned int*)0x1000);
}

// removeKeyboardHook(void*()) -> char* 
extern unsigned int _idt84;
void idt84() {
	removeKeyboardHook((void*)*(unsigned int*)0x1000);
	*(unsigned int*)0x1000 = (unsigned int)keyStates;
}

extern void initidtasm();
void initidt() {
	initpic();

	idthead(0, 32)
	idthead(1, 33)
	idthead(3, 35)
	idthead(4, 36)
	idthead(5, 37)
	idthead(6, 38)
	idthead(7, 39)
	idthead(8, 40)
	idthead(9, 41)
	idthead(10, 42)
	idthead(11, 43)
	idthead(12, 44)
	idthead(13, 45)
	idthead(14, 46)
	idthead(15, 47)

	idthead(70, 70)
	idthead(71, 71)
	idthead(72, 72)
	idthead(73, 73)
	idthead(74, 74)
	idthead(75, 75)

	idthead(76, 76)
	idthead(77, 77)
	idthead(78, 78)

	idthead(79, 79)

	idthead(80, 80)
	idthead(81, 81)
	idthead(82, 82)

	idthead(83, 83)
	idthead(84, 84)

	initidtasm();
}
