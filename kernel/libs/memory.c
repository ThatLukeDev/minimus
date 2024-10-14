void* malloc(unsigned int size) {
	return (void*)0x10000; // temporary
}

int __stack_chk_fail() {
	return 0;
}

// required by gcc
void* memcpy(void* dest, const void* src, unsigned int n) {
	char* pdest = (char*)dest;
	char* psrc = (char*)src;

	for (unsigned int i = 0; i < n; i++) {
		pdest[i] = psrc[i];
	}

	return dest;
}

void* memset(void* s, int c, unsigned int n) {
	char* pdest = (char*)s;

	for (unsigned int i = 0; i < n; i++) {
		pdest[i] = (char)c;
	}

	return s;
}

void* memmove(void* dest, const void* src, unsigned int n) {
	char* pdest = (char*)dest;
	const char* psrc = (const char*)src;

	if (src > dest) {
		for (unsigned int i = 0; i < n; i++) {
			pdest[i] = psrc[i];
		}
	}
	else if (src < dest) {
		for (unsigned int i = n; i > 0; i--) {
			pdest[i-1] = psrc[i-1];
		}
	}

	return dest;
}

int memcmp(const void* s1, const void* s2, unsigned int n) {
	const char* p1 = (const char*)s1;
	const char* p2 = (const char*)s2;

	for (unsigned int i = 0; i < n; i++) {
		if (p1[i] != p2[i]) {
			return p1[i] < p2[i] ? -1 : 1;
		}
	}

	return 0;
}
