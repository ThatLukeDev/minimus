void outb(unsigned short port, unsigned char val) {
	__asm__ volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

unsigned char inb(unsigned short port) {
	unsigned char _ret = 0;

	__asm__ volatile ("inb %w1, %b0" : "=a"(_ret) : "Nd"(port) : "memory");

	return _ret;
}

void iowait() {
	outb(0x80, 0);
}
