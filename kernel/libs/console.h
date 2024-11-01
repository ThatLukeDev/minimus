#ifndef LIB_CONSOLE
#define LIB_CONSOLE

extern char* cursor;

extern void clrscr();

extern void putc(char c);

extern void puts(char* s);

extern void printf(char* str, ...);

extern unsigned char showConsoleOutput;

extern char getc();
extern char* gets();

#endif
