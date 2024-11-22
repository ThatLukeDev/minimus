int strcmp(char* s1, char* s2) {
	const char* p1 = (const char*)s1;
	const char* p2 = (const char*)s2;

	for (int i = 0; p1[i] != 0; i++) {
		if (p1[i] != p2[i]) {
			return p1[i] < p2[i] ? -1 : 1;
		}
	}

	return 0;
}

int strlen(char* str) {
	char* ptr = str;

	while (*ptr != 0) {
		ptr++;
	}

	return ptr - str;
}
