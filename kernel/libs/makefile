OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
ASMOBJS := $(patsubst %.asm,%.o,$(wildcard *.asm))

lib.o: $(ASMOBJS) $(OBJS)
	ar cr $@ $^

$(OBJS): %.o: %.c
	gcc -m32 -c $^ -Wno-builtin-declaration-mismatch -o $@ -mno-sse -mno-red-zone

$(ASMOBJS): %.o: %.asm
	nasm -f elf32 $^ -o $@

.PHONY: clean
clean:
	rm *.o
