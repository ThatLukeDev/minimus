void* malloc(unsigned int size) {
	*(unsigned int*)0x1000 = size;
	__asm__ volatile ("int $76");
	return (*(void**)0x1000);
}

int free(void* ptr) {
	*(unsigned int*)0x1000 = (unsigned int)ptr;
	__asm__ volatile ("int $77");
	return (*(int*)0x1000);
}

void* realloc(void* ptr, unsigned int size) {
	*(unsigned int*)0x1000 = (unsigned int)ptr;
	*(unsigned int*)0x1010 = size;
	__asm__ volatile ("int $78");
	return (*(void**)0x1000);
}

void* calloc(unsigned int size, unsigned int n) {
	int len = size * n;
	void* ret = malloc(len);

	for (unsigned int i = 0; i < len; i++) {
		*((char*)ret+i) = 0;
	}

	return ret;
}

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

int __stack_chk_fail() {
	return 0;
}
int __stack_chk_fail_local() {
	return 0;
}
