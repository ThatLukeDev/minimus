#ifndef INT_CONSOLE
#define INT_CONSOLE

extern void clrscr();

extern void putc(char c);

extern void puts(char* s);

extern void printf(char* str, ...);

extern void showConsoleOutput();

extern char getc();
extern char* gets();

#endif
