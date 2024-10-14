#ifndef LIB_MEMORY
#define LIB_MEMORY

void initheap();

void* malloc(unsigned int size);
int free(void* ptr);
void* calloc(unsigned int size, unsigned int n);
void* realloc(void* ptr, unsigned int size);

int __stack_chk_fail();
int __stack_chk_fail_local();

// required by gcc
void* memcpy(void* dest, const void* src, unsigned int n);
void* memset(void* s, int c, unsigned int n);
void* memmove(void* dest, const void* src, unsigned int n);
int memcmp(const void* s1, const void* s2, unsigned int n);

#endif
