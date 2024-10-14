lib.o: *.c
	gcc -m32 -c -o $@ $< -Wno-builtin-declaration-mismatch

.PHONY: clean
clean:
	rm lib.o
