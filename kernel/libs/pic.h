#ifndef PIC_LIB
#define PIC_LIB

extern void (*picFunc[16][16])();

extern int addPicFunc(int pic, void (*func)());

#endif
