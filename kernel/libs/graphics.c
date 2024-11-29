#include "vga.h"

void drawfill(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b) {
	for (int x = x1; x <= x2; x++) {
		for (int y = y1; y <= y2; y++) {
			drawpixel(x, y, r, g, b);
		}
	}
}

void drawoutline(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b) {
	for (int x = x1; x <= x2; x++) {
		drawpixel(x, y1, r, g, b);
		drawpixel(x, y2, r, g, b);
	}
	for (int y = y1; y <= y2; y++) {
		drawpixel(x1, y, r, g, b);
		drawpixel(x2, y, r, g, b);
	}
}

void drawtext(int _x, int _y, char* str, unsigned char r, unsigned char g, unsigned char b) {
	for (; *str != 0; str++) {
		unsigned char* fontchar = font + ((int)(*str) * 16);

		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 8; x++) {
				if (fontchar[y] & (0b10000000 >> x)) {
					drawpixel(_x * 8 + x, _y * 16 + y, r, g, b);
				}
			}
		}
	}
}
