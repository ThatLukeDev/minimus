#include "vga.h"
#include "image.h"

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

void drawtext(char* str, int _x, int _y, int scale, unsigned char r, unsigned char g, unsigned char b) {
	font = (unsigned char*)0x1100; // defined in bootloader/main.asm

	for (int i = 0; *str != 0; str++) {
		unsigned char* fontchar = font + ((int)(*str) * 16);

		int perscale = scale / 16 + 1;
		for (int y = 0; y < 16 * perscale; y += perscale) {
			for (int x = 0; x < 8 * perscale; x += perscale) {
				if (fontchar[y / perscale] & (0b10000000 >> (x / perscale))) {
					for (int xscale = 0; xscale < perscale; xscale++) {
						for (int yscale = 0; yscale < perscale; yscale++) {
							drawpixel(_x + x + i * 8 * perscale + xscale, _y + y + yscale, r, g, b);
						}
					}
				}
			}
		}

		i++;
	}
}

void drawimage(struct image img, int _x, int _y) {
	for (int x = 0; x < img.width; x++) {
		for (int y = 0; y < img.height; y++) {
			unsigned char* pix = img.data + (x + y * img.width) * 3;
			drawpixel(x + _x, y + _y, pix[0], pix[1], pix[2]);
		}
	}
}
