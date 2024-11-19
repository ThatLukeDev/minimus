#include "ioutils.h"

extern void getvgafont();

#define VGA_MEM (unsigned char*)0xa0000
#define VGA_WIDTH 320
#define VGA_HEIGHT 200

#define VBE_WIDTH 640
#define VBE_HEIGHT 480
unsigned char vbeEnabled = 0;
unsigned char vbeAlpha = 3;
unsigned char* vbeFramebuffer = (unsigned char*)0x0;

unsigned char* font = (unsigned char*)0x1000; // defined in bootloader/main.asm

void drawpixel(int _x, int _y, unsigned char r, unsigned char g, unsigned char b) {
	if (vbeEnabled) {
		*(vbeFramebuffer + _x * vbeAlpha + vbeAlpha - 3 + _y * VBE_WIDTH * vbeAlpha) = r;
		*(vbeFramebuffer + _x * vbeAlpha + vbeAlpha - 2 + _y * VBE_WIDTH * vbeAlpha) = g;
		*(vbeFramebuffer + _x * vbeAlpha + vbeAlpha - 1 + _y * VBE_WIDTH * vbeAlpha) = b;
	}
	else {
		_x /= 2;
		_y /= 3;
		*(VGA_MEM + _x + _y * VGA_WIDTH) = (r & 0b11100000) | ((g >> 3) & 0b00011100) | ((b >> 6) & 0b00000011);
	}
}

void clrvga() {
	if (vbeEnabled) {
		for (int x = 0; x < VBE_WIDTH; x++) {
			for (int y = 0; y < VBE_HEIGHT; y++) {
				drawpixel(x, y, 0x00, 0x00, 0x00);
			}
		}
	}
	else {
		for (int x = 0; x < VGA_WIDTH; x++) {
			for (int y = 0; y < VGA_HEIGHT; y++) {
				drawpixel(x, y, 0x00, 0x00, 0x00);
			}
		}
	}
}

void drawchar(int _x, int _y, unsigned char _char) {
	unsigned char* fontchar = font + ((int)_char * 16);

	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 8; x++) {
			if (fontchar[y] & (0b10000000 >> x)) {
				drawpixel(_x * 8 + x, _y * 16 + y, 0xff, 0xff, 0xff);
			}
			else {
				drawpixel(_x * 8 + x, _y * 16 + y, 0x00, 0x00, 0x00);
			}
		}
	}
}

void initvga() {
	vbeEnabled = *(unsigned char*)0x2200;
	if (*(unsigned char*)0x2201)
		vbeAlpha = 4;
	else
		vbeAlpha = 3;

	if (vbeEnabled) {
		vbeFramebuffer = (unsigned char*)(*(unsigned int*)0x2202);
	}
	else {
		for (int i = 0; i < 256; i++) {
			unsigned char r = (i & 0b11100000) >> 2; // highest value is 0b00111111 as 18 bit colour space
			unsigned char g = (i & 0b00011100) << 1;
			unsigned char b = (i & 0b00000011) << 4; // used less bits for blue as eyes are less sensitive

			outb(0x3c8, i); // set DAC address
			outb(0x3c9, r); // set DAC R for i
			outb(0x3c9, g); // set DAC G for i
			outb(0x3c9, b); // set DAC B for i
		}
	}
}
