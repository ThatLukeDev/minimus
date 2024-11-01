#include "pic.h"

// interrupts.h
void interrupthandler(unsigned char interrupt) {
	for (int i = 0; i < 16; i++)
		if (picFunc[interrupt][i])
		picFunc[interrupt][i]();
}
