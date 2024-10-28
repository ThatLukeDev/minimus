#ifndef LIB_IOUTILS
#define LIB_IOUTILS

void outb(unsigned short port, unsigned char val);
unsigned char inb(unsigned short port);
void iowait();

#endif
