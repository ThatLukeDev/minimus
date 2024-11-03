#ifndef CLOCK_LIB
#define CLOCK_LIB

extern unsigned long ticks;
extern double runtime;

extern void pitsleep(double time);

extern void initclock();

#endif
