#ifndef INT_CONSOLE
#define INT_CONSOLE

extern void clrscr() __attribute__((always_inline));

extern void putc(char c) __attribute__((always_inline));

extern void puts(char* s) __attribute__((always_inline));

extern void printf(char* str, ...);

extern void showConsoleOutput() __attribute__((always_inline));

extern char getc() __attribute__((always_inline));
extern char* gets() __attribute__((always_inline));

#endif
