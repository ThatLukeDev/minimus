#ifndef INT_MEMORY
#define INT_MEMORY

#include "memory.c"

extern inline void* malloc(unsigned int size) __attribute__((always_inline));

extern inline int free(void* ptr) __attribute__((always_inline));

extern inline void* realloc(void* ptr, unsigned int size) __attribute__((always_inline));

#endif
