#ifndef GRAPHICS_LIB
#define GRAPHICS_LIB

extern void drawfill(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);

extern void drawoutline(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);

extern void drawtext(char* str, int _x, int _y, int scale, unsigned char r, unsigned char g, unsigned char b);

#endif
