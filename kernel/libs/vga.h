#ifndef VGA_LIB
#define VGA_LIB

extern void drawpixel(int _x, int _y, unsigned char code);

extern void drawchar(int _x, int _y, unsigned char _char);

extern void initvga();

extern void clrvga();

#endif
