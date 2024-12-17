#include "console.h"
#include "memory.h"
#include "vga.h"
#include "graphics.h"

int main() {
	printf("Hello World!\n");
	char* mem = malloc(1000);
	printf("1000 bytes: %x\n", mem);

	for (int i = 10; i < 100; i += 10)
		drawoutline(i, i, 640 - i, 480 - i, 255, 255, 255);

	drawfill(100, 100, 640-100, 480-100, 255, 0, 0);

	char* text = "Hello World!";
	drawtext(text, 150, 150, 32, 0, 0, 255);

	return 0;
}
