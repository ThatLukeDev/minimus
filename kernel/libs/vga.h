#ifndef VGA_LIB
#define VGA_LIB

extern void drawpixel(int _x, int _y, unsigned char r, unsigned char g, unsigned char b);

extern void drawchar(int _x, int _y, unsigned char _char);

extern void initvga();

extern void clrvga();

extern unsigned char* font;
extern unsigned char vbeEnabled;
extern unsigned char vbeAlpha;
extern unsigned char* vbeFramebuffer;

#endif
