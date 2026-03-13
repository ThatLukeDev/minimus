#define MAX_CLOCK_FREQ 1193182
#define CLOCK_FREQ 1000
#define CLOCK_DIVISIONS (MAX_CLOCK_FREQ / CLOCK_FREQ)

unsigned long getticks() {
	__asm__ volatile ("int $85");
	return (*(unsigned long*)0x1000);
}

void pitsleep(unsigned long milliseconds) {
	unsigned long desired = getticks() + milliseconds * CLOCK_DIVISIONS / 1000;

	while (1) {
		if (getticks() > desired) {
			return;
		}
	}
}
