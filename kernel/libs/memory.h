#ifndef LIB_MEMORY
#define LIB_MEMORY

void* malloc(unsigned int size);
int __stack_chk_fail();

// required by gcc
void* memcpy(void* dest, const void* src, unsigned int n);
void* memset(void* s, int c, unsigned int n);
void* memmove(void* dest, const void* src, unsigned int n);
int memcmp(const void* s1, const void* s2, unsigned int n);

#endif
