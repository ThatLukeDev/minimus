#ifndef PIC_LIB
#define PIC_LIB

void (*picFunc[16][16])();

int addPicFunc(int pic, void (*func)());

#endif
