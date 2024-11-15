#ifndef CLOCK_LIB
#define CLOCK_LIB

extern unsigned long ticks;

void pitsleep(unsigned int milliseconds);

extern void initclock();

#endif
