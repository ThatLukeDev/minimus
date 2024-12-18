#ifndef INT_MEMORY
#define INT_MEMORY

extern void* malloc(unsigned int size);
extern int free(void* ptr);
extern void* realloc(void* ptr, unsigned int size);

extern void* memcpy(void* dest, const void* src, unsigned int n);
extern void* memset(void* s, int c, unsigned int n);
extern void* memmove(void* dest, const void* src, unsigned int n);
extern int memcmp(const void* s1, const void* s2, unsigned int n);

#endif
