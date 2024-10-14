#ifndef LIB_CONSOLE
#define LIB_CONSOLE

extern char* cursor;

void clrscr();

void putc(char c);

void puts(char* s);

void printf(char* str, ...);

#endif
