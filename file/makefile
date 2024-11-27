OBJS := $(wildcard files/*)

bin/blob: $(OBJS) bin/compiler
	bin/compiler

bin/compiler: compiler.c
	gcc $^ -o $@

.PHONY: clean
clean:
	rm bin/*
