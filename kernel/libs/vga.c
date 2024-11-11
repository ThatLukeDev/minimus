extern void getvgafont();

#define VGA_MEM (unsigned char*)0xa0000
#define VGA_WIDTH 200
#define VGA_HEIGHT 320

unsigned char* font = (unsigned char*)0x1000; // defined in bootloader/main.asm

void drawpixel(unsigned char code, int _x, int _y) {
	*(VGA_MEM + _x + _y * VGA_HEIGHT) = code;
}

void drawchar(unsigned char _char, int _x, int _y) {
	unsigned char* fontchar = font + ((int)_char * 16);

	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 8; x++) {
			drawpixel(_x * 8 + x, _y * 16 + y, fontchar[y] & (1 << x)); // bit to byte
		}
	}
}
