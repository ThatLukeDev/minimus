#ifndef VGA_INT
#define VGA_INT

extern void drawpixel(int _x, int _y, unsigned char r, unsigned char g, unsigned char b);

extern void drawchar(int _x, int _y, unsigned char _char);

extern unsigned char* font;

#endif
