OBJS := $(wildcard files/*)

bin/blob: $(OBJS) bin/compiler
	bin/compiler

bin/compiler: compiler.c bin
	gcc $< -o $@

bin:
	mkdir bin

.PHONY: clean
clean:
	rm bin/*
