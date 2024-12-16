out.min: bin/out.bin
	cp $< $@

bin/out.bin: bin/out.elf
	objcopy -O binary $^ $@

bin/out.elf: bin/out.o libs/lib.o
	ld -m elf_i386 $^ -o $@ -T libs/link.ld

bin/out.o: main.c libs/lib.o bin
	gcc -Ilibs -m32 -ffreestanding -ffunction-sections -c $< -o $@ -fPIC -mno-sse

libs/lib.o: libs/*.h libs/*.c
	cd libs && make

bin:
	mkdir $@

.PHONY: clean
clean:
	cd libs && make clean
	rm bin/*
	rm out.min
