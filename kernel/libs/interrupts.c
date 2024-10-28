#define PIC1 0x20 // master pic
#define PIC2 0xa0 // slave pic

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

void initpic() {
}

extern unsigned int _idt0;
void idt0() {
	printf("Interrupt\n");
}

extern void initidtasm();
void initidt() {
	initidtelement(0, (unsigned int)&_idt0, 1);
	initidtasm();
}
