#ifndef LIB_MEMORY
#define LIB_MEMORY

extern void initheap();

extern void* malloc(unsigned int size);
extern int free(void* ptr);
extern void* calloc(unsigned int size, unsigned int n);
extern void* realloc(void* ptr, unsigned int size);

extern int __stack_chk_fail();
extern int __stack_chk_fail_local();

// required by gcc
extern void* memcpy(void* dest, const void* src, unsigned int n);
extern void* memset(void* s, int c, unsigned int n);
extern void* memmove(void* dest, const void* src, unsigned int n);
extern int memcmp(const void* s1, const void* s2, unsigned int n);

#endif
