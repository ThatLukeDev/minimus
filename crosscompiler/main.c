#include "console.h"
#include "memory.h"
#include "vga.h"
#include "graphics.h"
#include "file.h"

int main() {
	for (int i = 10; i < 100; i += 10)
		drawoutline(i, i, 640 - i, 480 - i, 255, 255, 255);

	drawfill(100, 100, 640-100, 480-100, 255, 0, 0);

	char* text = "Hello World!";
	drawtext(text, 150, 150, 32, 0, 0, 255);

	char* filename = "image.ppm";
	unsigned char* ppmimage = fileRead(filename);
	struct image img = loadPPM(ppmimage);
	free(ppmimage);

	drawimage(img, 128, 192);
	free(img.data);

	return 0;
}
