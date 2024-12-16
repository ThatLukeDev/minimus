#ifndef INT_CONSOLE
#define INT_CONSOLE

#include "console.c"

extern inline void clrscr() __attribute__((always_inline));

extern inline void putc(char c) __attribute__((always_inline));

extern inline void puts(char* s) __attribute__((always_inline));

extern void printf(char* str, ...);

extern inline void showConsoleOutput(char val) __attribute__((always_inline));

extern char getc() __attribute__((always_inline));
extern char* gets() __attribute__((always_inline));

#endif
