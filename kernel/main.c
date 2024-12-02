#include "ioutils.h"
#include "strutils.h"
#include "memory.h"
#include "console.h"
#include "interrupts.h"
#include "pic.h"
#include "clock.h"
#include "vga.h"
#include "mouse.h"
#include "disk.h"
#include "file.h"
#include "graphics.h"
#include "image.h"
#include "audio.h"

void main() {
	initheap();
	initconsole();
	clrscr();
	initvga();
	initidt();
	initclock();
	initfs();
	initaudio();

	unsigned char* audio = malloc(1000);
	for (int i = 0; i < 1000; i++) {
		audio[i] = audio[i-1] * i * i * i * i * 2412412142 - 14921331321;
	}

	playaudio(audio, 1000);
}
