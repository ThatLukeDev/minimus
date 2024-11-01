extern void (*picFunc[16][16])();

int addPicFunc(int pic, void (*func)()) {
	for (int i = 0; i < 16; i++) {
		if (!picFunc[pic][i]) {
			picFunc[pic][i] = func;
			return 0;
		}
	}
	return -1;
}

// interrupts.h
void interrupthandler(unsigned char interrupt) {
	for (int i = 0; i < 16; i++)
		if (picFunc[interrupt][i])
		picFunc[interrupt][i]();
}
