struct memchunk {
	struct memchunk* prev;
	struct memchunk* next;
	unsigned int size;
	char occupied;
};

struct memchunk* heap = (struct memchunk*)0x11000;
void initheap() {
	heap->size = 100000; // temporary
	heap->occupied = 0;
}

void* malloc(unsigned int size) {
	struct memchunk* check = heap;
	do {
		if (check->size > size + 16 && !check->occupied) {
			struct memchunk* nextchunk = check + size + 16;

			nextchunk->size = check->size - size - 16;
			nextchunk->prev = check;
			nextchunk->next = check->next;
			nextchunk->occupied = 0;

			check->prev = 0;
			check->next = nextchunk;
			check->size = size + 16;
			check->occupied = 1;

			return check + 16;
		}

		check = check->next;
	} while (check);
	return 0;
}

struct memchunk* m_memchunkstartfreesegment(struct memchunk* check) {
	if (check->prev && !check->prev->occupied)
		return m_memchunkstartfreesegment(check->prev);
	return check;
}

int free(void* ptr) {
	struct memchunk* check = ptr - 16;

	if ((check->prev && check->prev->next != check) || (check->next && check->next->prev != check)) {
		return 1;
	}

	check->occupied = 0;

	check = m_memchunkstartfreesegment(check);
	while (check->next && !check->next->occupied) {
		check->size += check->next->size;
		check->next = check->next->next;
	}
	if (check->next)
		check->next->prev = check;

	return 0;
}

void* realloc(void* ptr, unsigned int size) { // temporary (slow)
	void* _ptr = malloc(size);

	for (unsigned int i = 0; i < size; i++) {
		*((char*)_ptr+i) = *((char*)ptr+i);
	}

	free(ptr);

	return _ptr;
}

void* calloc(unsigned int size, unsigned int n) {
	int len = size * n;
	void* ret = malloc(len);

	for (unsigned int i = 0; i < len; i++) {
		*((char*)ret+i) = 0;
	}

	return ret;
}

int __stack_chk_fail() {
	return 0;
}
int __stack_chk_fail_local() {
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
