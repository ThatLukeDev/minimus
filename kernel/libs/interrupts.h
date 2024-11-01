#ifndef LIB_INTERRUPT
#define LIB_INTERRUPT

struct idtelement {
	unsigned short offset1; // offset 0-15
	unsigned short selector; // a code segment selector in gdt
	unsigned char base; // segment base
	unsigned char attr; // gate type, dpl, and p fields
	unsigned short offset2; // offset 16-31
};

extern void initidt();

extern void interrupthandler(unsigned char interrupt);

#endif
