OBJS := $(patsubst %.c,%.o,$(wildcard *.c))

lib.o: $(OBJS)
	ar cr $@ $^

$(OBJS): %.o: %.c
	gcc -m32 -c $^ -Wno-builtin-declaration-mismatch -o $@

.PHONY: clean
clean:
	rm *.o
