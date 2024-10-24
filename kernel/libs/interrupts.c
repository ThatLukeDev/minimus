#include "console.h" //temp

struct idtelement {
	unsigned short offset1; // offset 0-15
	unsigned short selector; // a code segment selector in gdt
	unsigned char base; // segment base (reserved)
	unsigned char attr; // gate type, dpl, and p fields (leftmost bit must be 1)
	unsigned short offset2; // offset 16-31
};

extern void* idtdescriptor;

// https://en.wikipedia.org/wiki/Interrupt_descriptor_table
void initidtelement(unsigned int num, void* func) {
	struct idtelement* element = (struct idtelement*)((void*)idtdescriptor+num*8);
	element->base = 0;
	element->selector = 0x7c27;
	element->attr = 0x08;//0b10001110;
	element->offset1 = (unsigned short)((unsigned int)func >> 8);
	element->offset2 = (unsigned short)((unsigned int)func);
}

extern void* _idthandler0;
void _idtfunc0() {
	printf("Interrupt\n");
}

extern void initidtasm();
void initidt() {
	initidtelement(0, _idthandler0);
	initidtasm();
}
