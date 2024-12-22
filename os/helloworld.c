#include "console.h"
#include "memory.h"
#include "vga.h"
#include "graphics.h"
#include "file.h"
#include "strutils.h"

int main() {
	char* args = *(char**)0x1000;

	char* text = "Hello World!";

	if (!strcmp(args, "-h")) {
		printf("USAGE: helloworld [TEXT?]\n");

		printf("Outputs a nice pretty picture and the text specified in blue\n");

		return -1;
	}

	if (args) {
		text = args;
	}

	for (int i = 10; i < 100; i += 10)
		drawoutline(i, i, 640 - i, 480 - i, 255, 255, 255);

	drawfill(100, 100, 640-100, 480-100, 255, 0, 0);

	drawtext(text, 150, 150, 32, 0, 0, 255);

	char* filename = "image.ppm";
	unsigned char* ppmimage = fileRead(filename);
	struct image img = loadPPM(ppmimage);
	free(ppmimage);

	drawimage(img, 128, 192);
	free(img.data);

	return 0;
}
