bin/os.img: bin bin/os.bin
	dd if=/dev/zero of=$@ count=2280
	dd if=bin/os.bin of=$@ conv=notrunc

bin/os.bin: bin/bootloader.bin bin/kernel.bin
	cat $^ > $@

bin/bootloader.bin: bootloader/main.asm
	nasm $^ -f bin -o $@

kernel/libs/lib.o: kernel/libs/*.h kernel/libs/*.c
	cd kernel/libs && make

bin/kernel.o: kernel/main.c kernel/libs/lib.o
	gcc -Ikernel/libs -m32 -ffreestanding -c $< -o $@ -fno-PIC -mno-sse

bin/kernel.elf: bin/kernel.o kernel/libs/lib.o
	ld -m elf_i386 $^ -o $@

bin/kernel.bin: bin/kernel.elf
	objcopy -O binary -j .text $^ $@

bin:
	mkdir $@

.PHONY: clean
clean:
	cd kernel/libs && make clean
	rm bin/*
