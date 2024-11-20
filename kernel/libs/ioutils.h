#ifndef LIB_IOUTILS
#define LIB_IOUTILS

extern void outb(unsigned short port, unsigned char val);
extern unsigned char inb(unsigned short port);
void outw(unsigned short port, unsigned short val);
unsigned char inw(unsigned short port);
extern void iowait();

#endif
