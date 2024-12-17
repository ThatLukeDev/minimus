unsigned char* font = (unsigned char*)0x1100; // defined in bootloader/main.asm

void drawpixel(int _x, int _y, unsigned char r, unsigned char g, unsigned char b) {
	*(int*)0x1000 = _x;
	*(int*)0x1010 = _y;
	*(char*)0x1020 = r;
	*(char*)0x1021 = g;
	*(char*)0x1022 = b;
	__asm__ volatile ("int $79");
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
